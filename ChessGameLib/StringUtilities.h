///////////////////////////////////////////////////////////////////////////////
// Filename: StringUtilities.h 
// Author: Adam Gladstone 
// Date: Monday, October 21, 2019
// 
// Description
//    
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(CLSGEN_STRINGUTILSEX_H__897A14E6_C57D_4245_9E5F_89AA69F86A4A__INCLUDED_)
#define CLSGEN_STRINGUTILSEX_H__897A14E6_C57D_4245_9E5F_89AA69F86A4A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include <locale>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdarg>
#include <string>
#include <vector>
#include <regex>

/////////////////////////////////////////////////////////////////////////////////
// Types

#undef min

/////////////////////////////////////////////////////////////////////////////////
// Globals

namespace Utilities
{
	namespace String
	{
		const std::string sDigits("0123456789");

		inline bool nocase_compare (char c1, char c2)
		{
			return toupper(c1) == toupper(c2);
		}

		/*
		struct IsSpace : public std::unary_function<char, bool>
		{
			inline bool operator() (char tchar) { return std::isspace(tchar, std::locale()); }
		};
		*/

		// compare case insensitive
		inline static bool CompareNoCase(const std::string& s1, const std::string& s2)
		{
			return (s1.size() == s2.size() && std::equal (s1.begin(), s1.end(), s2.begin(), nocase_compare));
		}

		inline void TrimLeft(std::string& s)
		{
			auto NotSpace = [](char tchar) { 
				return !std::isspace(tchar, std::locale()); 
			};

			std::basic_string<char>::iterator it = std::find_if(s.begin(), s.end(), NotSpace);
			if ( s.end() != it ) // avoid  assignment when possible
			{
				std::basic_string<char>::traits_type().move(&(*s.begin()), &(*it), (s.end() - it+1) * sizeof(char));
				s.resize(s.end() - it);
			}
		}

		inline void TrimLeft(std::string& s, char tTrim)
		{
			s.erase(0, s.find_first_not_of(tTrim));
		}

		inline void TrimLeft(std::string& s, const char* szTrimChars)
		{
			s.erase(0, s.find_first_not_of(szTrimChars));
		}

		inline void TrimRight(std::string& s)
		{
			auto NotSpace = [](char tchar) {
				return !std::isspace(tchar, std::locale());
			};

			std::basic_string<char>::reverse_iterator it = std::find_if(s.rbegin(), s.rend(), NotSpace);
			if ( s.rend() != it )
				s.erase(s.rend() - it);

			s.erase(it != s.rend() ? s.find_last_of(*it) + 1 : 0);
		}

		inline void TrimRight(std::string& s, char tTrim)
		{
			std::size_t nIdx = s.find_last_not_of(tTrim);
			if ( std::string::npos == nIdx )
			{
				s.erase();
			}
			else
			{
				char tSave = s.at(nIdx);
				s.erase(nIdx, std::string::npos);	
				s.append(1, tSave);
			}
		}

		inline void TrimRight(std::string& s, const char* szTrimChars)
		{
			std::size_t nIdx = s.find_last_not_of(szTrimChars);
			if(std::string::npos == nIdx )
			{
				s.erase();
			}
			else
			{
				char tSave = s.at(nIdx);
				s.erase(nIdx, std::string::npos);	
				s.append(1, tSave);
			}
		}

		inline void Trim(std::string& s)
		{
			TrimLeft(s);
			TrimRight(s);
		}

		inline void MakeUpper(std::string& s)
		{
			std::use_facet<std::ctype<char> > ( std::locale() ).toupper( &s[0], &s[s.size()]);
		}

		inline void MakeLower(std::string& s)
		{
			std::use_facet<std::ctype<char> > ( std::locale() ).tolower( &s[0], &s[s.size()]);
		}

		inline void MakeReverse(std::string& s)
		{
			std::reverse(s.begin(), s.end());
		}

		inline std::size_t Remove(std::string& s, char ch)
		{
			std::size_t nIdx = 0;
			std::size_t nRemoved = 0;
			while((nIdx = s.find_first_of(ch)) != std::string::npos)
			{
				s.erase(nIdx, 1);
				nRemoved++;
			}
			return nRemoved;
		}

		inline std::size_t Remove(std::string& s, const std::string& sChars)
		{
			std::size_t nRemoved = 0;
			for(std::string::const_iterator i = sChars.begin(); i != sChars.end(); ++i)
			{
				nRemoved += Remove(s, *i);
			}
			return nRemoved;
		}

		inline std::size_t Remove(const std::string& s, char ch, std::string& ret)
		{
			ret = s;
			std::size_t nIdx = 0;
			std::size_t nRemoved = 0;
			while((nIdx = ret.find_first_of(ch)) != std::string::npos)
			{
				ret.erase(nIdx, 1);
				nRemoved++;
			}
			return nRemoved;
		}

		inline std::size_t Remove(const std::string& s, const std::string& sChars, std::string& ret)
		{
			ret = s;
			std::size_t nRemoved = 0;
			for(std::string::const_iterator i = sChars.begin(); i != sChars.end(); ++i)
			{
				nRemoved += Remove(ret, *i);
			}
			return nRemoved;
		}

		inline std::size_t Replace(std::string& s, char chFind, char chReplace)
		{
			std::size_t nReplaced = 0;
			for(std::string::iterator iter = s.begin(); iter != s.end(); ++iter)
			{
				if(*iter == chFind)
				{
					*iter = chReplace;
					nReplaced++;
				}
			}
			return nReplaced;
		}

		inline std::size_t Replace(const std::string& s, char chFind, char chReplace, std::string& ret)
		{
			ret = s;
			std::size_t nReplaced = 0;
			for(std::string::iterator iter = ret.begin(); iter != ret.end(); ++iter)
			{
				if(*iter == chFind)
				{
					*iter = chReplace;
					nReplaced++;
				}
			}
			return nReplaced;
		}

		inline std::size_t Replace(std::string& s, const std::string& find, const std::string& replace)
		{
			std::size_t nReplaced = 0;
			std::string ret;
			std::string::size_type pos = s.find_first_of(find, 0);
			std::string::size_type lastPos = s.find_first_not_of(find, 0);

			if(pos == std::string::npos)
			{
				// search string not found in source
				return nReplaced;
			}

			if(pos == 0)
			{
				ret.append(replace);
				pos = s.find_first_of(find, lastPos);
				nReplaced++;
			}

			while(std::string::npos != pos && std::string::npos != lastPos)
			{
				ret.append(s.substr(lastPos, pos - lastPos));
				ret.append(replace);
				nReplaced++;
				lastPos = s.find_first_not_of(find, pos);
				pos = s.find_first_of(find, lastPos);
			}

			if(lastPos != std::string::npos)
			{
				ret.append(s.substr(lastPos, s.length() - lastPos));
				nReplaced++;
			}

			s = ret;
			return nReplaced;
		}

		inline std::size_t Replace(const std::string& s, const std::string& find, const std::string& replace, std::string& ret)
		{
			std::size_t nReplaced = 0;
			std::string::size_type pos = s.find_first_of(find, 0);
			std::string::size_type lastPos = s.find_first_not_of(find, 0);

			if(pos == std::string::npos)
			{
				// search string not found in source
				ret = s;
				return nReplaced;
			}

			if(pos == 0)
			{
				ret.append(replace);
				pos = ret.find_first_of(find, lastPos);
				nReplaced++;
			}

			while(std::string::npos != pos && std::string::npos != lastPos)
			{
				ret.append(s.substr(lastPos, pos - lastPos));
				ret.append(replace);
				nReplaced++;
				lastPos = s.find_first_not_of(find, pos);
				pos = s.find_first_of(find, lastPos);
			}

			if(lastPos != std::string::npos)
			{
				ret.append(s.substr(lastPos, s.length() - lastPos));
				nReplaced++;
			}

			return nReplaced;
		}

		inline int Find(const std::string& s, char ch)
		{
			std::size_t nIdx = s.find_first_of(ch);
			return static_cast<int>(nIdx == std::string::npos ? -1 : nIdx);
		}

		inline int Find(const std::string& s, const char* szSub)
		{
			std::size_t nIdx = s.find(szSub);
			return static_cast<int>(nIdx == std::string::npos ? -1 : nIdx);
		}

		inline int Find(const std::string& s, char ch, std::size_t nStart)
		{
			// must add 1 because Find excludes first character
			std::size_t nIdx = s.find_first_of(ch, static_cast<std::size_t>(nStart + 1));
			return static_cast<int>(nIdx == std::string::npos ? -1 : nIdx);
		}

		inline int Find(const std::string& s, const char* szSub, std::size_t nStart)
		{
			// must add 1 because Find excludes first character
			std::size_t nIdx = s.find(szSub, static_cast<std::size_t>(nStart + 1));
			return static_cast<int>(nIdx == std::string::npos ? -1 : nIdx);
		}

		inline int FindOneOf(const std::string& s, const char* szCharSet)
		{
			std::size_t nIdx = s.find_first_of(szCharSet);
			return static_cast<int>(nIdx == std::string::npos ? -1 : nIdx);
		}

		inline int ReverseFind(const std::string& s, char ch)
		{
			std::size_t nIdx = s.find_last_of(ch);
			return static_cast<int>(nIdx == std::string::npos ? -1 : nIdx);
		}

		inline std::string Left(const std::string& s, std::size_t nCount)
		{
			return s.substr(0, nCount); 
		}

		inline std::string Right(const std::string& s, std::size_t nCount)
		{
			nCount = std::min(nCount, s.size());
			return s.substr(s.size()-nCount);
		}

		inline std::string Mid(const std::string& s, std::size_t nFirst)
		{
			return s.substr(nFirst);
		}

		inline std::string Mid(const std::string& s, std::size_t nFirst, std::size_t nCount)
		{
			return s.substr(nFirst, nCount);
		}

		inline bool IsDigits(const std::string& s)
		{
			std::size_t nIdx = s.find_first_not_of(sDigits);
			return nIdx == std::string::npos ? true : false;
		}

		inline bool IsNumber(const std::string& s)
		{
			static const std::regex e("\\s[+|-]\\d+");
			return std::regex_match(s, e);
		}

		inline void StripWhitespace(std::string& s)
		{
			[[maybe_unused]]
			const auto ret = std::remove_if(s.begin(), s.end(), isspace);
		}

		inline std::size_t CountChar(const std::string& s, char c)
		{
			std::string::size_type n = 0;
			std::string::const_iterator i;
			for( i = s.begin(); i != s.end(); i++ )
			{
				if( c == (*i) ) n++;
			}
			return n;
		}

		inline bool ParseDelimited(
			std::vector<std::string>& vSplit, 
			const std::string& s, 
			const char *delimiters, 
			std::string& sError
		)
		{
			bool ok = true;

			typedef enum
			{
				STARTSECTION = 0,
				NOTSTRING = 1,
				INSTRING = 2,
				INSTRING_UNMATCHEDQUOTE = 3
			} e_splitMode;

			std::size_t inputlen = s.length();

			// temporary buffer to assemble strings in
			std::vector<char> buf(inputlen + 1);
			char *bufptr = &buf[0];

			// clear output area
			vSplit.clear();

			int pos = 0;
			const char *pc = s.c_str();
			e_splitMode mode = STARTSECTION;
			while( ok && *pc != '\0' )
			{
				if( *pc == '"' )
				{
					// We have hit a quote
					// If we are in a string already, notify we might be at the end
					// If we hit 2 quotes together, turn this notification off
					switch( mode )
					{
					case STARTSECTION:
						// We now know we are in a string
						// Don't add the character to output buffer
						mode = INSTRING;
						break;
					case NOTSTRING:
						// We shouldn't have any quotes unless the section
						// started with one.
						{
							std::ostringstream oss;
							oss << "StringUtils::split: quote found in non-string section at position " << pos << " in line (" << s << ")" << std::ends;
							sError = oss.str();
							ok = false;
						}
						break;
					case INSTRING:
						// Flag we've met a quote, in case the section is ending
						// Don't add the character to output buffer
						mode = INSTRING_UNMATCHEDQUOTE;
						break;
					case INSTRING_UNMATCHEDQUOTE:
						// We've met a double quote, which should resolve to a single one
						// Add single quote to output buffer
						*bufptr = '"';
						bufptr++;
						mode = INSTRING;
						break;
					default:
						{
							std::ostringstream oss;
							oss << "StringUtils::split: unknown mode (" << mode << ") at position " << pos << " in line (" << s << ")" << std::ends;
							sError = oss.str();
							ok = false;
						}
						break;
					}
				}
				else if( 0 != strchr(delimiters, *pc) )
				{
					// We have hit a delimiter
					// If inside string, write it out as normal character
					switch( mode )
					{
					case STARTSECTION: // Empty section
					case NOTSTRING: // Completed non-string section
					case INSTRING_UNMATCHEDQUOTE: // Completed string section
						{
							// write out buffer
							*bufptr = '\0';
							vSplit.push_back(&buf[0]);
							// reset buffer
							bufptr = &buf[0];
							// set to "start of section"
							mode = STARTSECTION;
						}
						break;
					case INSTRING:
						// Add character to output buffer
						*bufptr = *pc;
						bufptr++;
						break;
					default:
						{
							std::ostringstream oss;
							oss << "StringUtils::split: unknown mode (" << mode << ") at position " << pos << " in line (" << s << ")" << std::ends;
							sError = oss.str();
							ok = false;
						}
						break;
					}
				}
				else
				{
					// Something else
					// If we reached the end of a string, but there's no
					// delimiter, raise an error
					switch( mode )
					{
					case STARTSECTION:
						// We now know we are NOT in a string
						mode = NOTSTRING;
						// Add character to output buffer
						*bufptr = *pc;
						bufptr++;
						break;
					case INSTRING_UNMATCHEDQUOTE:
						// Bad format: a section should not contain a double quote
						// unless it starts with one.
						{
							std::ostringstream oss;
							oss << "StringUtils::split: unmatched quote at position " << pos << " in line (" << s << ")" << std::ends;
							sError = oss.str();
							ok = false;
						}
						break;
					default:
						// Add character to output buffer
						*bufptr = *pc;
						bufptr++;
						break;
					}
				}
				pc++;
				pos++;
			}

			if( ok )
			{
				// write out buffer for last section
				*bufptr = '\0';
				vSplit.push_back(&buf[0]);
			}

			return ok;
		}

		inline std::string FormatString(const char *pszFmt, ...)
		{
			const std::size_t MAX_BUFFER = 1024;
			static char szBuffer[MAX_BUFFER]{0};
			va_list ptr; 
			va_start(ptr, pszFmt);
			vsnprintf(szBuffer, MAX_BUFFER, pszFmt, ptr);
			va_end(ptr);
			return std::string(szBuffer);
		}
	}
}

#endif		//CLSGEN_STRINGUTILSEX_H__897A14E6_C57D_4245_9E5F_89AA69F86A4A__INCLUDED_
