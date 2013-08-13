//
//  main.cpp
//  TestIsKeyword
//
//  Created by Thaddaeus Frogley on 12/07/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <list>

#include <time.h>
#include <sys/time.h>

using namespace std;

bool IsCppKeyword(const char* c)
{
    switch(c[0]){
        case 'a':
        case 'A':
            switch(c[1]){
                case 'l':
                case 'L':
                    switch(c[2]){
                        case 'i':
                        case 'I':
                            switch(c[3]){
                                case 'g':
                                case 'G':
                                    switch(c[4]){
                                        case 'n':
                                        case 'N':
                                            switch(c[5]){
                                                case 'a':
                                                case 'A':
                                                    // alignas
                                                    return strcasecmp(c+6, "s")==0;
                                                case 'o':
                                                case 'O':
                                                    // alignof
                                                    return strcasecmp(c+6, "f")==0;
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case 'n':
                case 'N':
                    switch(c[2]){
                        case 'd':
                        case 'D':
                            switch(c[3]){
                                case 0:
                                    // and
                                    return true;
                                case '_':
                                    // and_eq
                                    return strcasecmp(c+4, "eq")==0;
                            }
                            break;
                    }
                    break;
                case 's':
                case 'S':
                    // asm
                    return strcasecmp(c+2, "m")==0;
                case 'u':
                case 'U':
                    // auto
                    return strcasecmp(c+2, "to")==0;
            }
            break;
        case 'b':
        case 'B':
            switch(c[1]){
                case 'i':
                case 'I':
                    switch(c[2]){
                        case 't':
                        case 'T':
                            switch(c[3]){
                                case 'a':
                                case 'A':
                                    // bitand
                                    return strcasecmp(c+4, "nd")==0;
                                case 'o':
                                case 'O':
                                    // bitor
                                    return strcasecmp(c+4, "r")==0;
                            }
                            break;
                    }
                    break;
                case 'o':
                case 'O':
                    // bool
                    return strcasecmp(c+2, "ol")==0;
                case 'r':
                case 'R':
                    // break
                    return strcasecmp(c+2, "eak")==0;
            }
            break;
        case 'c':
        case 'C':
            switch(c[1]){
                case 'a':
                case 'A':
                    switch(c[2]){
                        case 's':
                        case 'S':
                            // case
                            return strcasecmp(c+3, "e")==0;
                        case 't':
                        case 'T':
                            // catch
                            return strcasecmp(c+3, "ch")==0;
                    }
                    break;
                case 'h':
                case 'H':
                    switch(c[2]){
                        case 'a':
                        case 'A':
                            switch(c[3]){
                                case 'r':
                                case 'R':
                                    switch(c[4]){
                                        case 0:
                                            // char
                                            return true;
                                        case '1':
                                            // char16_t
                                            return strcasecmp(c+5, "6_t")==0;
                                        case '3':
                                            // char32_t
                                            return strcasecmp(c+5, "2_t")==0;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case 'l':
                case 'L':
                    // class
                    return strcasecmp(c+2, "ass")==0;
                case 'o':
                case 'O':
                    switch(c[2]){
                        case 'm':
                        case 'M':
                            // compl
                            return strcasecmp(c+3, "pl")==0;
                        case 'n':
                        case 'N':
                            switch(c[3]){
                                case 's':
                                case 'S':
                                    switch(c[4]){
                                        case 't':
                                        case 'T':
                                            switch(c[5]){
                                                case 0:
                                                    // const
                                                    return true;
                                                case '_':
                                                    // const_cast
                                                    return strcasecmp(c+6, "cast")==0;
                                                case 'e':
                                                case 'E':
                                                    // constexpr
                                                    return strcasecmp(c+6, "xpr")==0;
                                            }
                                            break;
                                    }
                                    break;
                                case 't':
                                case 'T':
                                    // continue
                                    return strcasecmp(c+4, "inue")==0;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 'd':
        case 'D':
            switch(c[1]){
                case 'e':
                case 'E':
                    switch(c[2]){
                        case 'c':
                        case 'C':
                            // decltype
                            return strcasecmp(c+3, "ltype")==0;
                        case 'f':
                        case 'F':
                            // default
                            return strcasecmp(c+3, "ault")==0;
                        case 'l':
                        case 'L':
                            // delete
                            return strcasecmp(c+3, "ete")==0;
                    }
                    break;
                case 'o':
                case 'O':
                    // double
                    return strcasecmp(c+2, "uble")==0;
                case 'y':
                case 'Y':
                    // dynamic_cast
                    return strcasecmp(c+2, "namic_cast")==0;
            }
            break;
        case 'e':
        case 'E':
            switch(c[1]){
                case 'l':
                case 'L':
                    // else
                    return strcasecmp(c+2, "se")==0;
                case 'n':
                case 'N':
                    // enum
                    return strcasecmp(c+2, "um")==0;
                case 'x':
                case 'X':
                    switch(c[2]){
                        case 'p':
                        case 'P':
                            switch(c[3]){
                                case 'l':
                                case 'L':
                                    // explicit
                                    return strcasecmp(c+4, "icit")==0;
                                case 'o':
                                case 'O':
                                    // export
                                    return strcasecmp(c+4, "rt")==0;
                            }
                            break;
                        case 't':
                        case 'T':
                            // extern
                            return strcasecmp(c+3, "ern")==0;
                    }
                    break;
            }
            break;
        case 'f':
        case 'F':
            switch(c[1]){
                case 'a':
                case 'A':
                    // false
                    return strcasecmp(c+2, "lse")==0;
                case 'l':
                case 'L':
                    // float
                    return strcasecmp(c+2, "oat")==0;
                case 'o':
                case 'O':
                    // for
                    return strcasecmp(c+2, "r")==0;
                case 'r':
                case 'R':
                    // friend
                    return strcasecmp(c+2, "iend")==0;
            }
            break;
        case 'g':
        case 'G':
            // goto
            return strcasecmp(c+1, "oto")==0;
        case 'i':
        case 'I':
            switch(c[1]){
                case 'f':
                case 'F':
                    // if
                    return c[2]==0;
                case 'n':
                case 'N':
                    switch(c[2]){
                        case 'l':
                        case 'L':
                            // inline
                            return strcasecmp(c+3, "ine")==0;
                        case 't':
                        case 'T':
                            // int
                            return c[3]==0;
                    }
                    break;
            }
            break;
        case 'l':
        case 'L':
            // long
            return strcasecmp(c+1, "ong")==0;
        case 'm':
        case 'M':
            // mutable
            return strcasecmp(c+1, "utable")==0;
        case 'n':
        case 'N':
            switch(c[1]){
                case 'a':
                case 'A':
                    // namespace
                    return strcasecmp(c+2, "mespace")==0;
                case 'e':
                case 'E':
                    // new
                    return strcasecmp(c+2, "w")==0;
                case 'o':
                case 'O':
                    switch(c[2]){
                        case 'e':
                        case 'E':
                            // noexcept
                            return strcasecmp(c+3, "xcept")==0;
                        case 't':
                        case 'T':
                            switch(c[3]){
                                case 0:
                                    // not
                                    return true;
                                case '_':
                                    // not_eq
                                    return strcasecmp(c+4, "eq")==0;
                            }
                            break;
                    }
                    break;
                case 'u':
                case 'U':
                    // nullptr
                    return strcasecmp(c+2, "llptr")==0;
            }
            break;
        case 'o':
        case 'O':
            switch(c[1]){
                case 'p':
                case 'P':
                    // operator
                    return strcasecmp(c+2, "erator")==0;
                case 'r':
                case 'R':
                    switch(c[2]){
                        case 0:
                            // or
                            return true;
                        case '_':
                            // or_eq
                            return strcasecmp(c+3, "eq")==0;
                    }
                    break;
            }
            break;
        case 'p':
        case 'P':
            switch(c[1]){
                case 'r':
                case 'R':
                    switch(c[2]){
                        case 'i':
                        case 'I':
                            // private
                            return strcasecmp(c+3, "vate")==0;
                        case 'o':
                        case 'O':
                            // protected
                            return strcasecmp(c+3, "tected")==0;
                    }
                    break;
                case 'u':
                case 'U':
                    // public
                    return strcasecmp(c+2, "blic")==0;
            }
            break;
        case 'r':
        case 'R':
            switch(c[1]){
                case 'e':
                case 'E':
                    switch(c[2]){
                        case 'g':
                        case 'G':
                            // register
                            return strcasecmp(c+3, "ister")==0;
                        case 'i':
                        case 'I':
                            // reinterpret_cast
                            return strcasecmp(c+3, "nterpret_cast")==0;
                        case 't':
                        case 'T':
                            // return
                            return strcasecmp(c+3, "urn")==0;
                    }
                    break;
            }
            break;
        case 's':
        case 'S':
            switch(c[1]){
                case 'h':
                case 'H':
                    // short
                    return strcasecmp(c+2, "ort")==0;
                case 'i':
                case 'I':
                    switch(c[2]){
                        case 'g':
                        case 'G':
                            // signed
                            return strcasecmp(c+3, "ned")==0;
                        case 'z':
                        case 'Z':
                            // sizeof
                            return strcasecmp(c+3, "eof")==0;
                    }
                    break;
                case 't':
                case 'T':
                    switch(c[2]){
                        case 'a':
                        case 'A':
                            switch(c[3]){
                                case 't':
                                case 'T':
                                    switch(c[4]){
                                        case 'i':
                                        case 'I':
                                            switch(c[5]){
                                                case 'c':
                                                case 'C':
                                                    switch(c[6]){
                                                        case 0:
                                                            // static
                                                            return true;
                                                        case '_':
                                                            switch(c[7]){
                                                                case 'a':
                                                                case 'A':
                                                                    // static_assert
                                                                    return strcasecmp(c+8, "ssert")==0;
                                                                case 'c':
                                                                case 'C':
                                                                    // static_cast
                                                                    return strcasecmp(c+8, "ast")==0;
                                                            }
                                                            break;
                                                    }
                                                    break;
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                        case 'r':
                        case 'R':
                            // struct
                            return strcasecmp(c+3, "uct")==0;
                    }
                    break;
                case 'w':
                case 'W':
                    // switch
                    return strcasecmp(c+2, "itch")==0;
            }
            break;
        case 't':
        case 'T':
            switch(c[1]){
                case 'e':
                case 'E':
                    // template
                    return strcasecmp(c+2, "mplate")==0;
                case 'h':
                case 'H':
                    switch(c[2]){
                        case 'i':
                        case 'I':
                            // this
                            return strcasecmp(c+3, "s")==0;
                        case 'r':
                        case 'R':
                            switch(c[3]){
                                case 'e':
                                case 'E':
                                    // thread_local
                                    return strcasecmp(c+4, "ad_local")==0;
                                case 'o':
                                case 'O':
                                    // throw
                                    return strcasecmp(c+4, "w")==0;
                            }
                            break;
                    }
                    break;
                case 'r':
                case 'R':
                    switch(c[2]){
                        case 'u':
                        case 'U':
                            // true
                            return strcasecmp(c+3, "e")==0;
                        case 'y':
                        case 'Y':
                            // try
                            return c[3]==0;
                    }
                    break;
                case 'y':
                case 'Y':
                    switch(c[2]){
                        case 'p':
                        case 'P':
                            switch(c[3]){
                                case 'e':
                                case 'E':
                                    switch(c[4]){
                                        case 'd':
                                        case 'D':
                                            // typedef
                                            return strcasecmp(c+5, "ef")==0;
                                        case 'i':
                                        case 'I':
                                            // typeid
                                            return strcasecmp(c+5, "d")==0;
                                        case 'n':
                                        case 'N':
                                            // typename
                                            return strcasecmp(c+5, "ame")==0;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 'u':
        case 'U':
            switch(c[1]){
                case 'n':
                case 'N':
                    switch(c[2]){
                        case 'i':
                        case 'I':
                            // union
                            return strcasecmp(c+3, "on")==0;
                        case 's':
                        case 'S':
                            // unsigned
                            return strcasecmp(c+3, "igned")==0;
                    }
                    break;
                case 's':
                case 'S':
                    // using
                    return strcasecmp(c+2, "ing")==0;
            }
            break;
        case 'v':
        case 'V':
            switch(c[1]){
                case 'i':
                case 'I':
                    // virtual
                    return strcasecmp(c+2, "rtual")==0;
                case 'o':
                case 'O':
                    switch(c[2]){
                        case 'i':
                        case 'I':
                            // void
                            return strcasecmp(c+3, "d")==0;
                        case 'l':
                        case 'L':
                            // volatile
                            return strcasecmp(c+3, "atile")==0;
                    }
                    break;
            }
            break;
        case 'w':
        case 'W':
            switch(c[1]){
                case 'c':
                case 'C':
                    // wchar_t
                    return strcasecmp(c+2, "har_t")==0;
                case 'h':
                case 'H':
                    // while
                    return strcasecmp(c+2, "ile")==0;
            }
            break;
        case 'x':
        case 'X':
            switch(c[1]){
                case 'o':
                case 'O':
                    switch(c[2]){
                        case 'r':
                        case 'R':
                            switch(c[3]){
                                case 0:
                                    // xor
                                    return true;
                                case '_':
                                    // xor_eq
                                    return strcasecmp(c+4, "eq")==0;
                            }
                            break;
                    }
                    break;
            }
            break;
    }
    return false;
}


bool IsCppKeywordHelper2(const char * a, const char * b){
    return strcasecmp(a,b)<0;
}
bool IsCppKeyword2(const char* c)
{
    static const char* k[83] = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class", "compl", "const", "const_cast", "constexpr", "continue", "decltype", "default", "delete", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq", };
    return std::binary_search(k, k+83, c, IsCppKeywordHelper2 );
}

// generated by: http://code.google.com/p/gen-is-keyword-fn/
bool IsCppKeyword3(const char* c, unsigned int l)
{
    switch(l){
        case 2:
            switch(c[0]){
                case 'I':
                case 'i':
                    // if
                    return c[1]=='f' || c[1]=='F';
                case 'O':
                case 'o':
                    // or
                    return c[1]=='r' || c[1]=='R';
            }
        case 3:
            switch(c[0]){
                case 'A':
                case 'a':
                    switch(c[1]){
                        case 'N':
                        case 'n':
                            // and
                            return c[2]=='d' || c[2]=='D';
                        case 'S':
                        case 's':
                            // asm
                            return c[2]=='m' || c[2]=='M';
                    }
                    break;
                case 'F':
                case 'f':
                    // for
                    return strncasecmp(c+1, "or", 2)==0;
                case 'I':
                case 'i':
                    // int
                    return strncasecmp(c+1, "nt", 2)==0;
                case 'N':
                case 'n':
                    switch(c[1]){
                        case 'E':
                        case 'e':
                            // new
                            return c[2]=='w' || c[2]=='W';
                        case 'O':
                        case 'o':
                            // not
                            return c[2]=='t' || c[2]=='T';
                    }
                    break;
                case 'T':
                case 't':
                    // try
                    return strncasecmp(c+1, "ry", 2)==0;
                case 'X':
                case 'x':
                    // xor
                    return strncasecmp(c+1, "or", 2)==0;
            }
        case 4:
            switch(c[0]){
                case 'A':
                case 'a':
                    // auto
                    return strncasecmp(c+1, "uto", 3)==0;
                case 'B':
                case 'b':
                    // bool
                    return strncasecmp(c+1, "ool", 3)==0;
                case 'C':
                case 'c':
                    switch(c[1]){
                        case 'A':
                        case 'a':
                            // case
                            return strncasecmp(c+2, "se", 2)==0;
                        case 'H':
                        case 'h':
                            // char
                            return strncasecmp(c+2, "ar", 2)==0;
                    }
                    break;
                case 'E':
                case 'e':
                    switch(c[1]){
                        case 'L':
                        case 'l':
                            // else
                            return strncasecmp(c+2, "se", 2)==0;
                        case 'N':
                        case 'n':
                            // enum
                            return strncasecmp(c+2, "um", 2)==0;
                    }
                    break;
                case 'G':
                case 'g':
                    // goto
                    return strncasecmp(c+1, "oto", 3)==0;
                case 'L':
                case 'l':
                    // long
                    return strncasecmp(c+1, "ong", 3)==0;
                case 'T':
                case 't':
                    switch(c[1]){
                        case 'H':
                        case 'h':
                            // this
                            return strncasecmp(c+2, "is", 2)==0;
                        case 'R':
                        case 'r':
                            // true
                            return strncasecmp(c+2, "ue", 2)==0;
                    }
                    break;
                case 'V':
                case 'v':
                    // void
                    return strncasecmp(c+1, "oid", 3)==0;
            }
        case 5:
            switch(c[1]){
                case 'A':
                case 'a':
                    switch(c[0]){
                        case 'C':
                        case 'c':
                            // catch
                            return strncasecmp(c+2, "tch", 3)==0;
                        case 'F':
                        case 'f':
                            // false
                            return strncasecmp(c+2, "lse", 3)==0;
                    }
                    break;
                case 'H':
                case 'h':
                    switch(c[0]){
                        case 'S':
                        case 's':
                            // short
                            return strncasecmp(c+2, "ort", 3)==0;
                        case 'T':
                        case 't':
                            // throw
                            return strncasecmp(c+2, "row", 3)==0;
                        case 'W':
                        case 'w':
                            // while
                            return strncasecmp(c+2, "ile", 3)==0;
                    }
                    break;
                case 'I':
                case 'i':
                    // bitor
                    return strncasecmp(c, "bitor", 5)==0;
                case 'L':
                case 'l':
                    switch(c[0]){
                        case 'C':
                        case 'c':
                            // class
                            return strncasecmp(c+2, "ass", 3)==0;
                        case 'F':
                        case 'f':
                            // float
                            return strncasecmp(c+2, "oat", 3)==0;
                    }
                    break;
                case 'N':
                case 'n':
                    // union
                    return strncasecmp(c, "union", 5)==0;
                case 'O':
                case 'o':
                    switch(c[2]){
                        case 'M':
                        case 'm':
                            // compl
                            return strncasecmp(c, "compl", 5)==0;
                        case 'N':
                        case 'n':
                            // const
                            return strncasecmp(c, "const", 5)==0;
                    }
                    break;
                case 'R':
                case 'r':
                    switch(c[0]){
                        case 'B':
                        case 'b':
                            // break
                            return strncasecmp(c+2, "eak", 3)==0;
                        case 'O':
                        case 'o':
                            // or_eq
                            return strncasecmp(c+2, "_eq", 3)==0;
                    }
                    break;
                case 'S':
                case 's':
                    // using
                    return strncasecmp(c, "using", 5)==0;
            }
        case 6:
            switch(c[1]){
                case 'E':
                case 'e':
                    switch(c[0]){
                        case 'D':
                        case 'd':
                            // delete
                            return strncasecmp(c+2, "lete", 4)==0;
                        case 'R':
                        case 'r':
                            // return
                            return strncasecmp(c+2, "turn", 4)==0;
                    }
                    break;
                case 'I':
                case 'i':
                    switch(c[2]){
                        case 'G':
                        case 'g':
                            // signed
                            return strncasecmp(c, "signed", 6)==0;
                        case 'T':
                        case 't':
                            // bitand
                            return strncasecmp(c, "bitand", 6)==0;
                        case 'Z':
                        case 'z':
                            // sizeof
                            return strncasecmp(c, "sizeof", 6)==0;
                    }
                    break;
                case 'N':
                case 'n':
                    switch(c[0]){
                        case 'A':
                        case 'a':
                            // and_eq
                            return strncasecmp(c+2, "d_eq", 4)==0;
                        case 'I':
                        case 'i':
                            // inline
                            return strncasecmp(c+2, "line", 4)==0;
                    }
                    break;
                case 'O':
                case 'o':
                    switch(c[0]){
                        case 'D':
                        case 'd':
                            // double
                            return strncasecmp(c+2, "uble", 4)==0;
                        case 'N':
                        case 'n':
                            // not_eq
                            return strncasecmp(c+2, "t_eq", 4)==0;
                        case 'X':
                        case 'x':
                            // xor_eq
                            return strncasecmp(c+2, "r_eq", 4)==0;
                    }
                    break;
                case 'R':
                case 'r':
                    // friend
                    return strncasecmp(c, "friend", 6)==0;
                case 'T':
                case 't':
                    switch(c[2]){
                        case 'A':
                        case 'a':
                            // static
                            return strncasecmp(c, "static", 6)==0;
                        case 'R':
                        case 'r':
                            // struct
                            return strncasecmp(c, "struct", 6)==0;
                    }
                    break;
                case 'U':
                case 'u':
                    // public
                    return strncasecmp(c, "public", 6)==0;
                case 'W':
                case 'w':
                    // switch
                    return strncasecmp(c, "switch", 6)==0;
                case 'X':
                case 'x':
                    switch(c[2]){
                        case 'P':
                        case 'p':
                            // export
                            return strncasecmp(c, "export", 6)==0;
                        case 'T':
                        case 't':
                            // extern
                            return strncasecmp(c, "extern", 6)==0;
                    }
                    break;
                case 'Y':
                case 'y':
                    // typeid
                    return strncasecmp(c, "typeid", 6)==0;
            }
        case 7:
            switch(c[0]){
                case 'A':
                case 'a':
                    switch(c[5]){
                        case 'A':
                        case 'a':
                            // alignas
                            return strncasecmp(c+1, "lignas", 6)==0;
                        case 'O':
                        case 'o':
                            // alignof
                            return strncasecmp(c+1, "lignof", 6)==0;
                    }
                    break;
                case 'D':
                case 'd':
                    // default
                    return strncasecmp(c+1, "efault", 6)==0;
                case 'M':
                case 'm':
                    // mutable
                    return strncasecmp(c+1, "utable", 6)==0;
                case 'N':
                case 'n':
                    // nullptr
                    return strncasecmp(c+1, "ullptr", 6)==0;
                case 'P':
                case 'p':
                    // private
                    return strncasecmp(c+1, "rivate", 6)==0;
                case 'T':
                case 't':
                    // typedef
                    return strncasecmp(c+1, "ypedef", 6)==0;
                case 'V':
                case 'v':
                    // virtual
                    return strncasecmp(c+1, "irtual", 6)==0;
                case 'W':
                case 'w':
                    // wchar_t
                    return strncasecmp(c+1, "char_t", 6)==0;
            }
        case 8:
            switch(c[2]){
                case 'A':
                case 'a':
                    switch(c[4]){
                        case '1':
                            // char16_t
                            return strncasecmp(c, "char16_t", 8)==0;
                        case '3':
                            // char32_t
                            return strncasecmp(c, "char32_t", 8)==0;
                    }
                    break;
                case 'C':
                case 'c':
                    // decltype
                    return strncasecmp(c, "decltype", 8)==0;
                case 'E':
                case 'e':
                    switch(c[0]){
                        case 'N':
                        case 'n':
                            // noexcept
                            return strncasecmp(c+1, "oexcept", 7)==0;
                        case 'O':
                        case 'o':
                            // operator
                            return strncasecmp(c+1, "perator", 7)==0;
                    }
                    break;
                case 'G':
                case 'g':
                    // register
                    return strncasecmp(c, "register", 8)==0;
                case 'L':
                case 'l':
                    // volatile
                    return strncasecmp(c, "volatile", 8)==0;
                case 'M':
                case 'm':
                    // template
                    return strncasecmp(c, "template", 8)==0;
                case 'N':
                case 'n':
                    // continue
                    return strncasecmp(c, "continue", 8)==0;
                case 'P':
                case 'p':
                    switch(c[0]){
                        case 'E':
                        case 'e':
                            // explicit
                            return strncasecmp(c+1, "xplicit", 7)==0;
                        case 'T':
                        case 't':
                            // typename
                            return strncasecmp(c+1, "ypename", 7)==0;
                    }
                    break;
                case 'S':
                case 's':
                    // unsigned
                    return strncasecmp(c, "unsigned", 8)==0;
            }
        case 9:
            switch(c[0]){
                case 'C':
                case 'c':
                    // constexpr
                    return strncasecmp(c+1, "onstexpr", 8)==0;
                case 'N':
                case 'n':
                    // namespace
                    return strncasecmp(c+1, "amespace", 8)==0;
                case 'P':
                case 'p':
                    // protected
                    return strncasecmp(c+1, "rotected", 8)==0;
            }
        case 10:
            // const_cast
            return strncasecmp(c, "const_cast", 10)==0;
        case 11:
            // static_cast
            return strncasecmp(c, "static_cast", 11)==0;
        case 12:
            switch(c[0]){
                case 'D':
                case 'd':
                    // dynamic_cast
                    return strncasecmp(c+1, "ynamic_cast", 11)==0;
                case 'T':
                case 't':
                    // thread_local
                    return strncasecmp(c+1, "hread_local", 11)==0;
            }
        case 13:
            // static_assert
            return strncasecmp(c, "static_assert", 13)==0;
        case 16:
            // reinterpret_cast
            return strncasecmp(c, "reinterpret_cast", 16)==0;
    }
    return false;
}

typedef std::list<char*> StringList;

StringList* BuildStringList(const char* filename)
{
    StringList* result=0;
    
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open())
    {
        result = new StringList();
        
        while ( myfile.good() )
        {
            getline (myfile,line);
            if (!line.empty())
            {       
                // tokenise
                std::string token;
                for(int c=0;c!=line.size();++c)
                {
                    if (isalnum(line[c]))
                    {
                        token+=line[c];
                    }
                    else
                    {
                        if (!token.empty())
                        {
                            result->push_back( strdup(token.c_str()) );
                            token.clear();
                        }
                    }
                }
            }
        }
        
        myfile.close();
    }
    
    return result;
}

timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

void GetTime( timespec& result )
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    result.tv_sec = tv.tv_sec;
    result.tv_nsec = tv.tv_usec*1000;
}

int main (int argc, const char * argv[])
{
    // insert code here...
    StringList* tokens = BuildStringList(argv[1]);
    
    if (tokens)
    {
        for (StringList::const_iterator i=tokens->begin();i!=tokens->end();++i)
        {
            if (IsCppKeyword2(*i) != IsCppKeyword(*i) || IsCppKeyword3(*i, strlen(*i))!=IsCppKeyword(*i))
            {
                std::cout << *i << " " << IsCppKeyword2(*i) << IsCppKeyword(*i) << IsCppKeyword3(*i, strlen(*i)) << endl;
            }
        }

        
        timespec time1, time2;
        GetTime(time1);
        
        int positives = 0;
        const int max_reps = 1000;
        for (int repeats = 0;repeats!=max_reps;repeats++)
        {
            for (StringList::const_iterator i=tokens->begin();i!=tokens->end();++i)
            {
                // if (IsCppKeyword(*i))
                if (IsCppKeyword2(*i))
                    positives++;
            }
        }   
              
        GetTime(time2);
        cout<<"found " << positives << " of " << tokens->size()*max_reps << endl;
        cout<<diff(time1,time2).tv_sec<<":"<<diff(time1,time2).tv_nsec<<endl;
    }
    
    // just let the OS sort out the memory leaks...
    return 0;
}

