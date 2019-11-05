// tokenizer.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "bloques.h"
#include <boost/tokenizer.hpp>
#include <string>
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
 /*std::string str = "for(int m = 0;m < 10;m++)";
  typedef boost::tokenizer<boost::char_separator<char> > 
    tokenizer;
  boost::char_separator<char> sep :: {"|","(",")","+","=","-",";"};
  string m = {"|","(",")","+","=","-",";"};
  tokenizer tokens(str, " ");
 
  for (tokenizer::iterator tok_iter = tokens.begin();
       tok_iter != tokens.end(); ++tok_iter)
	 
    std::cout << "<" << *tok_iter << "> " <<  endl;
  std::cout << "\n";
  */
	////////////////////////////////////////////////
/*	   using namespace std;
   using namespace boost;
   string s = "11111111";
   int offsets[] = {2,2,4};
   offset_separator f(offsets, offsets+1);
   typedef token_iterator_generator<offset_separator>::type Iter;
   Iter beg = make_token_iterator<string>(s.begin(),s.end(),f);
   Iter end = make_token_iterator<string>(s.end(),s.end(),f); 
   // The above statement could also have been what is below
   // Iter end;
   for(;beg!=end;++beg){
     cout << *beg << "\n";
   }*/
	////////////////////////////////////////////////
  /*  std::string str = ";;Hello|world||-foo--bar;yow;baz|";
  typedef boost::tokenizer<boost::char_separator<char> > 
    tokenizer;
  boost::char_separator<char> sep("-;|");
  tokenizer tokens(str, sep);
  for (tokenizer::iterator tok_iter = tokens.begin();
       tok_iter != tokens.end(); ++tok_iter)
    std::cout << "<" << *tok_iter << "> ";
  std::cout << "\n";
  */
	////////////////////////////////////////////////
/*	std::string str = ";;Hello|world||-foo--bar;yow;baz|";
    typedef boost::tokenizer<boost::char_separator<char> > 
        tokenizer;
    boost::char_separator<char> sep("-;", "|", boost::keep_empty_tokens);
    tokenizer tokens(str, sep);
    for (tokenizer::iterator tok_iter = tokens.begin();
         tok_iter != tokens.end(); ++tok_iter)
      std::cout << "<" << *tok_iter << "> ";
    std::cout << "\n";*/
	////////////////////////////////////////////////
    std::string str = "for(int m = 0; m < 10; m ++)";
    typedef boost::tokenizer<boost::char_separator<char> > 
        tokenizer;
	//boost::char_separator<char> sep("-;", "|", boost::keep_empty_tokens);
	//boost::char_separator<char> sep("| ","(=;)++<", boost::keep_empty_tokens);
    boost::char_separator<char> sep(" ","(=;)++<");
    tokenizer tokens(str, sep);
    for (tokenizer::iterator tok_iter = tokens.begin();
         tok_iter != tokens.end(); ++tok_iter)
		
		 std::cout << "<" << *tok_iter << "> " << "\n";
   
	getch();
	return 0;
}

