/** @file
File:       IccTagFactory.h

Contains:   Header for implementation of CIccTagFactory class and
creation factories

Version:    V1

Copyright:  � see ICC Software License
*/

/*
* The ICC Software License, Version 0.1
*
*
* Copyright (c) 2005 The International Color Consortium. All rights 
* reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer. 
*
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*
* 3. The end-user documentation included with the redistribution,
*    if any, must include the following acknowledgment:  
*       "This product includes software developed by the
*        The International Color Consortium (www.color.org)"
*    Alternately, this acknowledgment may appear in the software itself,
*    if and wherever such third-party acknowledgments normally appear.
*
* 4. In the absence of prior written permission, the names "ICC" and "The
*    International Color Consortium" must not be used to imply that the
*    ICC organization endorses or promotes products derived from this
*    software.
*
*
* THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED.  IN NO EVENT SHALL THE INTERNATIONAL COLOR CONSORTIUM OR
* ITS CONTRIBUTING MEMBERS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
* USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
* ====================================================================
*
* This software consists of voluntary contributions made by many
* individuals on behalf of the The International Color Consortium. 
*
*
* Membership in the ICC is encouraged when this software is used for
* commercial purposes. 
*
*  
* For more information on The International Color Consortium, please
* see <http://www.color.org/>.
*  
* 
*/

////////////////////////////////////////////////////////////////////// 
// HISTORY:
//
// -Oct 30, 2005 
//  A CIccTagCreator singleton class has been added to provide general
//  support for dynamically creating tag classes using a tag signature.
//  Prototype and private tag type support can be added to the system
//  by pushing additional IIccTagFactory based objects to the 
//  singleton CIccTagCreator object.
//
//////////////////////////////////////////////////////////////////////

#ifndef _ICCTAGXMLFACTORY_H
#define _ICCTAGXMLFACTORY_H

#include "IccTagFactory.h"

//CIccTag factory support
#ifdef USESAMPLEICCNAMESPACE
namespace sampleICC {
#endif

/**
***********************************************************************
* Class: CIccSpecTagFactory
*
* Purpose:
* CIccSpecTagFactory provides creation of CIccTag's defined by the ICC profile
* specification.  The CIccTagCreator always creates a CIccSpecTagFactory.
***********************************************************************
*/
class CIccTagXmlFactory : public IIccTagFactory
{
public:
  /**
  * Function: CreateTag(tagTypeSig)
  *  Create a tag of type tagTypeSig.
  *
  * Parameter(s):
  *  tagTypeSig = signature of the ICC tag type for the tag to be created
  *
  * Returns a new CIccTag object of the given signature type.
  * Unrecognized tagTypeSig's will be created as a CIccTagUnknown object.
  */
  virtual CIccTag* CreateTag(icTagTypeSignature tagSig);

  /**
  * Function: GetTagSigName(tagSig)
  *  Get display name of tagSig.
  *
  * Parameter(s):
  *  tagName = string to put tag name into, 
  *  tagSig = signature of the ICC tag type to get a name for
  *
  * Returns pointer to string containing name of tag if tag is recognized
  * by the factory, NULL if the factory doesn't create tagSig tags.
  */
  virtual const icChar* GetTagSigName(icTagSignature tagSig);

  /**
  * Function: GetTagTypeSigName(tagTypeSig)
  *  Get display name of tagTypeSig.
  *
  * Parameter(s):
  *  tagName = string to put tag name into, 
  *  tagTypeSig = signature of the ICC tag type to get a name for
  *
  * Returns pointer to string containing name of tag type if tag is recognized
  * by the factory, NULL if the factory doesn't create tagTypeSig tags.
  */
  virtual const icChar* GetTagTypeSigName(icTagTypeSignature tagTypeSig);
};

#ifdef USESAMPLEICCNAMESPACE
} //namespace sampleICC
#endif

#endif //_ICCTAGFACTORY_H
