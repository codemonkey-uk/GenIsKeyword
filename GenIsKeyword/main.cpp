/*
Copyright (c) 2011 Thaddaeus Frogley

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include <fstream>

#include <deque>
#include <list>
#include <map>

#include <algorithm>

#include <locale>

#include <assert.h>

#include <cstring>
#include <climits>

const int max_indent = 256;
const char* gOptions[256] = {};

bool CaseSensitive()
{
    return *gOptions['s']=='t' || *gOptions['s']=='T';
}

bool WideCharacterStrings()
{
	return tolower(*gOptions['c'])!='c';
}

bool CharICmp(char a, char b)
{
#ifdef _MSC_VER
    bool result = (_strnicmp(&a, &b, 1)==0);
#else
    bool result = (toupper(a) - toupper(b))==0;
#endif
    return result;
}

const char* StringCompareFn(bool fixedLength=false)
{
    // char
    if (!WideCharacterStrings())
    {
        if (CaseSensitive())
        {
            if (fixedLength)
            {
                return "strncmp";
            }
            else
            {
                return "strcmp";
            }
        }
        else
        {
            // case insensitive string compare is platform specific:
            if (tolower(*gOptions['p'])=='p')
            {
                if (fixedLength)
                {
                    return "strncasecmp";
                }
                else
                {
                    return "strcasecmp";    //POSIX
                }
            }
            else
            {
                if (fixedLength)
                {   
                    return "_strnicmp";
                }
                else
                {
                    return "_stricmp";      //Windows
                }
            }
        }
    }
    // not char, assume wide: "wchar_t"
    else
    {
        if (CaseSensitive())
        {
            if (fixedLength)
            {
                return "wcsncmp";
            }
            else
            {
                return "wcscmp";
            }
        }
        else
        {
            // case insensitive string compare is platform specific:
            if (tolower(*gOptions['p'])=='p')
            {
                //POSIX / GNU
                if (fixedLength)
                {
                    return "wcsncasecmp";
                }
                else
                {
                    return "wcscasecmp";
                }
            }
            else
			{
                //Windows
				if (fixedLength)
				{
					return "_wcsnicmp";      
				}
				else
				{
					return "_wcsicmp";
				}
			}
        }
    }
}

typedef std::deque<std::string> StringList;
typedef void(*AlgorithmPtr)(const StringList*);

typedef std::map<std::string, AlgorithmPtr> AlgorithmMap;

void GenerateCaseBlock(char c, char* indent, bool* mask=0)
{
    char c_array[3];
    int char_count = 0;
    
    c_array[char_count++] = c;
    
    if (!CaseSensitive())
    {
        if (c!=toupper(c))
            c_array[char_count++] = toupper(c);
        
        if (c!=tolower(c))
            c_array[char_count++] = tolower(c);
    }
    
    std::sort( c_array, c_array+char_count );
    for (int i=0;i!=char_count;++i)
    {
        std::cout << indent << "case '" << c_array[i] << "':" << std::endl;
        if (mask) mask[ c_array[i] ] = true;
    }
}

size_t GenSwitchCase(StringList::const_iterator b, StringList::const_iterator e, int depth = 0)
{
    const int base_indent = 2;
	assert( depth+base_indent+1 < max_indent );
    char indent[max_indent];
    
    memset(indent, ' ', depth+base_indent);
    indent[depth+base_indent] = 0;

    size_t result = std::distance(b,e);
    if (result>1)
    {
        std::cout << indent << "switch(c[" << depth << "]){" << std::endl;
        for (StringList::const_iterator i=b; i!=e;) {
            if (i->size()>depth)
            {
                GenerateCaseBlock((*i)[depth], indent);
                
                StringList::const_iterator j = i;
                while(j!=e && j->size()>depth && (*j)[depth]==(*i)[depth])
                {
                    j++;
                }
                
                if (GenSwitchCase(i, j, depth+1)>1)
                {
                    std::cout << indent << " break;" << std::endl;
                }
                
                i = j;
            }
            else
            {
                std::cout << indent << "case 0:" << std::endl;
                std::cout << indent << " // " << *i << std::endl;
                std::cout << indent << " return true;" << std::endl;
                
                ++i;
            }
        }
        std::cout << indent << "}" << std::endl;
    }
    else
    {
        std::cout << indent << "// " << *b << std::endl;
        if (b->size()>depth)
            std::cout << indent << "return " << StringCompareFn() << "(c+" << depth << ", \"" << &(*b)[depth] << "\")==0;" << std::endl;
        else
            std::cout << indent << "return c[" << depth << "]==0;" << std::endl;
    }
    
    return result;
}

void BuildSwitchCase(const StringList* words)
{
    std::cout << "bool Is" << gOptions['l'] << "Keyword(const " << gOptions['c'] << "* c)" << std::endl << "{" << std::endl;
    GenSwitchCase( words->begin(), words->end(), 0 );  
    std::cout << " return false;" << std::endl;
    std::cout << "}" << std::endl;
}

int MeasureMatchiness(StringList::const_iterator b, StringList::const_iterator e, int depth)
{
    int results[256] = {0,};
    int result = 0;
    
    for (StringList::const_iterator i=b; i!=e; ++i) {
        char c = (*i)[depth];

        int subTotal = ++results[c];
        if (!CaseSensitive())
        {
            if (c!=toupper(c))
                subTotal += results[toupper(c)];
            if (c!=tolower(c))
                subTotal += results[tolower(c)];                
        }
        if (subTotal > result)
            result = subTotal;
    }
    
    return result;
}

int SelectLeastMatchyDepth(StringList::const_iterator b, StringList::const_iterator e, bool* mask)
{
    int best_depth = 0;
    int least_matchiness = INT_MAX;
    for (int i=0;i!=b->size();++i)
    {
        if (!mask[i])
        {
            int matchiness = MeasureMatchiness(b,e,i);
            if (matchiness<least_matchiness)
            {
                best_depth = i;
                least_matchiness = matchiness;
            }
        
        }
    }
    
    return best_depth;
}

struct SortByNthLetterFn
{
    int mN;
    
    SortByNthLetterFn(int n)
    : mN(n)
    {}
    
    bool operator()(const std::string& a, const std::string& b)const
    {
        return a[mN] < b[mN];
    }
};

size_t GenPSwitchCase(const StringList::iterator b, const StringList::iterator e, bool* mask)
{
    int indent_depth = 3;
    for (int i=0;i!=b->size();++i)
        if (mask[i]) indent_depth ++;
    
	assert( indent_depth+1 < max_indent );
    char indent[max_indent];
    
    memset(indent, ' ', indent_depth);
    indent[indent_depth] = 0;
    
    size_t result = std::distance(b,e);
    if (result>1)
    {
        int depth = SelectLeastMatchyDepth(b, e, mask);
        mask[depth] = true;
        
        // generate the case statments in accending order
        std::sort( b, e, SortByNthLetterFn(depth) );
        
        std::cout << indent << "switch(c[" << depth << "]){" << std::endl;
        
        bool done[256] = {false,};
        for (StringList::const_iterator i=b; i!=e; ++i) {
            if (!done[(*i)[depth]])
            {                      
                GenerateCaseBlock((*i)[depth], indent, done);

                bool* new_mask = new bool[b->size()];
                std::copy(mask, mask+b->size(), new_mask);
                StringList newList;
                for (StringList::const_iterator j=b; j!=e; ++j) {
                    if (CharICmp((*i)[depth], (*j)[depth]))
                        newList.push_back(*j);
                }

                if (GenPSwitchCase(newList.begin(), newList.end(), new_mask)>1)
                {
                    std::cout << indent << " break;" << std::endl;
                }

				delete[] new_mask;
            }
        }
        std::cout << indent << "}" << std::endl;
    }
    else
    {
        int c1 = 0;
        while (c1<b->size() && mask[c1])
            c1++;
        
        int c2 = static_cast<int>(b->size());
        while (c2>c1 && mask[c2-1])
            c2--;
        
        std::cout << indent << "// " << *b << std::endl;
        if (b->size()>c1)
        {
            if (c2-c1==1)
            {
                std::cout << indent << "return c[" << c1 << "]=='" << (char)((*b)[c1]) << "'";
                if (!CaseSensitive())
                {
                    if ((*b)[c1]!=toupper((*b)[c1]))
                        std::cout << " || c[" << c1 << "]=='"<< (char)toupper((*b)[c1]) << "'";
                    
                    if ((*b)[c1]!=tolower((*b)[c1]))
                        std::cout << " || c[" << c1 << "]=='"<< (char)tolower((*b)[c1]) << "'";
                }
                std::cout << ";" << std::endl;
            }
            else
            {
                std::cout << indent << "return " << StringCompareFn(true) << "(c";
                if (c1>0)
                    std::cout << "+" << c1;
                std::cout << ", ";
				if (WideCharacterStrings())
					std::cout << "L";
				std::cout << "\"" << &(*b)[c1] << "\", " << (b->size()-c1) << ")==0;" << std::endl;
            }
        }
        else
        {
            std::cout << indent << "return true;" << std::endl;
        }
    }
    
    return result;
}

void BuildPSwitchCase(const StringList* words)
{
    std::cout << "bool Is" << gOptions['l'] << "Keyword(const " << gOptions['c'] << "* c, unsigned int l)" << std::endl << "{" << std::endl;
    
    // create partician
    std::map<size_t, StringList> p;
    for (StringList::const_iterator i=words->begin(); i!=words->end(); ++i)
    {
        p[i->length()].push_back( *i );
    }
    
    std::cout << " switch(l){" << std::endl;
    for (std::map<size_t, StringList>::iterator j=p.begin(); j!=p.end(); ++j)
    {
        std::cout << " case " << j->first << ":" << std::endl;
        bool* mask = new bool[j->first];
        std::fill(mask, mask+j->first, false);
        GenPSwitchCase( j->second.begin(), j->second.end(), mask );  
        delete[] mask;
    }
    std::cout << " }" << std::endl;
    
    std::cout << " return false;" << std::endl;
    std::cout << "}" << std::endl;
}

std::string GenBinarySearchHelperFn(std::string name)
{
    name += "Helper";
    std::cout << "bool " << name << "(const char * a, const char * b){" << std::endl;
    std::cout << " return " << StringCompareFn() << "(a,b)<0;" << std::endl << "}" << std::endl;
    return name;
}

void GenBinarySearchFnBody(StringList::const_iterator b, StringList::const_iterator e, const std::string& helper)
{
    size_t l = std::distance(b, e);
    std::cout << "static const char* k[" << l << "] = {" << std::endl;
    for (StringList::const_iterator i=b; i!=e;++i)
        std::cout << "\"" << *i << "\", ";
    std::cout << "};" << std::endl;
    std::cout << "return std::binary_search(k, k+" << l << ", c, " << helper << " );" << std::endl;
}

void BuildBinarySearch(const StringList* words)
{
    std::string fnName = "Is";
    fnName += gOptions['l'];
    fnName += "Keyword";
    
    std::string helperName = GenBinarySearchHelperFn(fnName);
    std::cout << "bool " << fnName << "(const " << gOptions['c'] << "* c)" << std::endl << "{" << std::endl;
    GenBinarySearchFnBody( words->begin(), words->end(), helperName );   
    std::cout << "}" << std::endl;
}

struct IsSeperator : std::unary_function<int,bool> {
    bool operator() (const int& c) const {return isspace(c) || strchr( gOptions['x'], c );}
};


// trim from start
static inline std::string ltrim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(IsSeperator())));
    return s;
}

// trim from end
static inline std::string rtrim(std::string s) {
    std::string::reverse_iterator r = std::find_if(s.rbegin(), s.rend(), std::not1(IsSeperator()));
    
    if (r==s.rend())
        return std::string("");
    
    s.erase(r.base(), s.end());
    return s;
}

// trim from both ends
static inline std::string trim(std::string s) {
    return ltrim(rtrim(s));
}

typedef std::pair< std::string, std::string > StringPair;

static inline StringPair split_string( const std::string& s )
{
    std::string::const_iterator mid1 = std::find_if(s.begin(), s.end(), IsSeperator());
    std::string::const_iterator mid2 = std::find_if(mid1, s.end(), std::not1(IsSeperator()));
    
    return StringPair( std::string(s.begin(), mid1), std::string(mid2, s.end()) );
}
                  
StringList* BuildStringList(std::istream& myfile)
{
    StringList* result=0;
    
    std::string line, word;
    result = new StringList();
        
    while ( myfile.good() )
    {
        getline (myfile,line);
        
        while (!line.empty())
        {
            StringPair split = split_string( line );
            word = trim(split.first);
            if (!word.empty())
            {
                result->push_back(word);
            }
            line = split.second;
        }
    }
        
    std::sort( result->begin(), result->end() );

    return result;
}

int main (int argc, const char * argv[])
{
    std::deque< const char* > filenames;
    
    // default options:
    gOptions['l'] = "";  // l=Language Type, ie l=Cpp to make IsCppKeyword function name
    gOptions['c'] = "char"; // c=Character Type, char or wchar_t
    gOptions['a'] = "pswitchcase"; // a=Algorithm
    gOptions['s'] = "t"; // s=case Sensitive (any word starting with t or T as true, f or F as false)
    gOptions['p'] = "POSIX"; // p=target Platform (POSIX vs Windows, checks vs first letter only, P or W)
    gOptions['x'] = ",";
    
    // algorithms
    AlgorithmMap algos;
    algos["switchcase"] = BuildSwitchCase;
    algos["pswitchcase"] = BuildPSwitchCase;
    algos["binary_search"] = BuildBinarySearch;
    
    for (int i=1;i!=argc;++i)
    {
        const char * arg = argv[i];
        if (*arg=='-')
        {
            if (arg[1]!=0 && arg[2]=='=')
            {
                gOptions[tolower(arg[1])] = arg+3;
            }
            else
            {
                std::cerr << "Error: Command line argument format not recognised:" << std::endl;
                std::cerr << "\t" << arg << std::endl;
                return -1;
            }
        }
        else
        {
            filenames.push_back(argv[i]);
        }
    }
    
    // read word list in, 
    StringList* words = 0;
    if (filenames.empty())
    {
        // from std input if no filenames on commandline
        words = BuildStringList(std::cin);
    }
    else
    {
        // from first filename on commandline if one is given
        std::ifstream myfile (filenames[0]);
        if (myfile.is_open())
        {
            words = BuildStringList(myfile);
            myfile.close();
        }    
    }
    
    if (words && !words->empty())
    {
        AlgorithmPtr fn = algos[ gOptions['a'] ];
        if (fn)
        {
			std::cout << "// generated by: http://code.google.com/p/gen-is-keyword-fn/" << std::endl;
            fn( words );   
        }
        else
        {
            std::cerr << "Error: Algorithm not found: " << gOptions['a'] << std::endl;
        }
        
        delete words;
    }
    else
    {
        std::cerr << "Error: Keyword list empty or not pressent." << std::endl;
        return -1;
    }
    
    return 0;
}

