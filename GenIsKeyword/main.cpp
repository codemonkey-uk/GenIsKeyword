//
//  main.cpp
//  GenIsKeyword
//
//  Created by Thaddaeus Frogley on 11/07/2011.
//  Copyright 2011 Thaddaeus Frogley. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <list>

typedef std::list<std::string> StringList;

void BuildIt(StringList::iterator b, StringList::iterator e, int depth = 0)
{
    char indent[depth+1];
    
    memset(indent, ' ', depth);
    indent[depth]=0;

    if (std::distance(b,e)>1)
    {
        std::cout << indent << "switch(c[" << depth << "]){" << std::endl;
        for (StringList::iterator i=b; i!=e;) {
            if (i->size()>depth)
            {
                std::cout << indent << "case '" << (*i)[depth] << "':" << std::endl;
                
                StringList::iterator j = i;
                while(j!=e && j->size()>depth && (*j)[depth]==(*i)[depth])
                {
                    j++;
                }
                
                if (i!=j)
                {
                    BuildIt(i, j, depth+1);
                }
                
                i = j;
                
                std::cout << indent << "break;" << std::endl;
            }
            else
            {
                std::cout << indent << "case 0: //" << *i << std::endl;
                std::cout << indent << "return true;" << std::endl;
                
                ++i;
            }
        }
        std::cout << indent << "}" << std::endl;
    }
    else
    {
        std::cout << indent << "// " << *b << std::endl;
        if (b->size()>depth)
            std::cout << indent << "return strcmp(c+" << depth << ", \"" << &(*b)[depth] << "\")==0;" << std::endl;
        else
            std::cout << indent << "return c[" << depth << "]==0;" << std::endl;
    }
}

StringList* BuildStringList()
{
    StringList* result=0;
    
    std::string line;
    std::ifstream myfile ("cpp_keywords.txt");
    if (myfile.is_open())
    {
        result = new StringList();
        
        while ( myfile.good() )
        {
            getline (myfile,line);
            result->push_back(line);
        }
        
        myfile.close();
    }

    return result;
}

int main (int argc, const char * argv[])
{
    std::cout << "// " << argv[0] << std::endl;
    StringList* words = BuildStringList();
    if (words)
    {
        std::string setName = "Cpp";
        std::cout << "bool Is" << setName << "Keyword(const char* c)" << std::endl << "{" << std::endl;
        BuildIt( words->begin(), words->end(), 0 );   
        std::cout << " return false;" << std::endl << "}" << std::endl;
        
        delete words;
    }
    
    return 0;
}

