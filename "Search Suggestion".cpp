class Solution {
    class TrieNode{
        public:
        map<char,TrieNode*> child;
        string name;
        bool isend=false;
    };
    class Trie{
        public:
        TrieNode* head=new TrieNode();
        void insert(string word){
            TrieNode* curr=head;
            for(auto letter: word){
                if(curr->child.find(letter)!=curr->child.end()){
                    curr=curr->child[letter];
                }
                else{
                    TrieNode* temp=new TrieNode();
                    curr->child.insert({letter,temp});
                    curr=curr->child[letter];
                }
            }
            curr->isend=true;
            curr->name=word;
        }
        vector<string> searchPrefix(string prefix){
            vector<string> ret;
            TrieNode* curr=head;
            int three=3;
            for(auto letter: prefix){
                if(curr->child.find(letter)!=curr->child.end()){
                    curr=curr->child[letter];
                }
                else{
                    return ret;
                }
            }
            stack<TrieNode*> st;
            st.push(curr);
            while(three&&!st.empty()){
                curr=st.top();
                st.pop();
                if(curr->isend){
                    three--;
                    ret.push_back(curr->name);
                }
                for(auto it=curr->child.rbegin();it!=curr->child.rend();it++){
                    st.push(it->second);
                }
            }
            return ret;
        }
    };
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie* t=new Trie();
        for(int i=0;i<products.size();i++){
            t->insert(products[i]);
        }
        vector<vector<string>> res;
        string wor;
        for(int i=0;i<searchWord.size();i++){
            wor.push_back(searchWord[i]);
            vector<string> temp=t->searchPrefix(wor);
            res.push_back(temp);
        }
        return res;
    }
};
