/*
 * libjingle
 * Copyright 2010, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TALK_P2P_BASE_PARSING_H_
#define TALK_P2P_BASE_PARSING_H_

#include <string>
#include <vector>
#include "talk/base/basictypes.h"
#include "talk/xmllite/xmlelement.h"  

namespace cricket {


struct ParseError {
 public:
  
  std::string text;
  
  const buzz::XmlElement* extra;

  ParseError() : extra(NULL) {}

  ~ParseError() {
    delete extra;
  }

  void SetText(const std::string& text) {
    this->text = text;
  }
};

struct WriteError {
  std::string text;

  void SetText(const std::string& text) {
    this->text = text;
  }
};

bool BadParse(const std::string& text, ParseError* err);

bool BadWrite(const std::string& text, WriteError* error);

std::string GetXmlAttr(const buzz::XmlElement* elem,
                       const buzz::QName& name,
                       const std::string& def);
std::string GetXmlAttr(const buzz::XmlElement* elem,
                       const buzz::QName& name,
                       const char* def);
bool GetXmlAttr(const buzz::XmlElement* elem,
                const buzz::QName& name, bool def);
int GetXmlAttr(const buzz::XmlElement* elem,
               const buzz::QName& name, int def);
void AddXmlAttr(buzz::XmlElement* elem,
                const buzz::QName& name, int n);
void SetXmlBody(buzz::XmlElement* elem, uint32 u);
const buzz::XmlElement* GetXmlChild(const buzz::XmlElement* parent,
                                    const std::string& name);
bool RequireXmlChild(const buzz::XmlElement* parent,
                     const std::string& name,
                     const buzz::XmlElement** child,
                     ParseError* error);
bool RequireXmlAttr(const buzz::XmlElement* elem,
                    const buzz::QName& name,
                    std::string* value,
                    ParseError* error);
void AddXmlChildren(buzz::XmlElement* parent,
                    const std::vector<buzz::XmlElement*>& children);
void CopyXmlChildren(const buzz::XmlElement* source, buzz::XmlElement* dest);
std::vector<buzz::XmlElement*> CopyOfXmlChildren(const buzz::XmlElement* elem);

}  

#endif  