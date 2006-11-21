/** @file
File:       IccTagMpe.h

Contains:   Header for implementation of CIccTagMultiProcessElement
and supporting classes

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
// -Jan 30, 2005 
//  Initial CIccFloatTag prototype development
//
// -Nov 6, 2006
//  Prototype Merged into release
//
//////////////////////////////////////////////////////////////////////

#ifndef _ICCTAGMPE_H
#define _ICCTAGMPE_H

#include "IccTag.h"
#include "IccTagFactory.h"
#include "icProfileHeader.h"
#include <memory>
#include <list>


//CIccFloatTag support
#ifdef USESAMPLEICCNAMESPACE
namespace sampleICC {
#endif

typedef enum {
  icElemInterpLinear,
  icElemInterpTetra,
} icElemInterp;

class CIccTagMultiProcessElement;
class CIccMultiProcessElement;

/**
****************************************************************************
* Class: CIccProcessElementPtr
* 
* Purpose: Get std list class to work with pointers to elements rather than
*  element objects so they can be shared.
*****************************************************************************
*/
class CIccMultiProcessElementPtr
{
public:
  CIccMultiProcessElement *ptr;
};

typedef std::list<CIccMultiProcessElementPtr> CIccMultiProcessElementList;
typedef CIccMultiProcessElementList::iterator CIccMultiProcessElementIter;

#define icSigMpeLevel0 ((icSignature)0x6D706530)  /* 'mpe0' */

/**
****************************************************************************
* Class: CIccMultiProcessElement
* 
* Purpose: Base Class for Multi Process Elements
*****************************************************************************
*/
class CIccMultiProcessElement
{
public:
  CIccMultiProcessElement() { m_sigBaseLevel = icSigMpeLevel0; }

  virtual ~CIccMultiProcessElement() {}
  
  static CIccMultiProcessElement* CIccMultiProcessElement::Create(icElemTypeSignature sig);

  virtual CIccMultiProcessElement *NewCopy() const = 0;

  virtual icElemTypeSignature GetType() const = 0;
  virtual const icChar *GetClassName() const = 0;

  virtual icUInt16Number NumInputChannels() const { return m_nInputChannels; }
  virtual icUInt16Number NumOutputChannels() const { return m_nOutputChannels; }

  virtual bool IsSupported() { return true; }

  virtual void Describe(std::string &sDescription) = 0;

  virtual bool Read(icUInt32Number size, CIccIO *pIO) = 0;
  virtual bool Write(CIccIO *pIO) = 0;

  virtual bool Begin(icElemInterp nIterp=icElemInterpLinear, CIccTagMultiProcessElement *pMPE=NULL) = 0;
  virtual void Apply(icFloatNumber *pDestPixel, const icFloatNumber *pSrcPixel) = 0;

  virtual icValidateStatus Validate(icTagSignature sig, std::string &sReport, const CIccTagMultiProcessElement* pMPE=NULL) const = 0;

  icSignature GetBaseLevel() { return m_sigBaseLevel; }

  //Future Acs Expansion Element Accessors
  virtual bool IsAcs() { return false; }
  virtual icAcsSignature GetBAcsSig() { return icSigAcsZero; }
  virtual icAcsSignature GetEAcsSig() { return icSigAcsZero; }

protected:
  icUInt32Number m_nReserved;
  icUInt16Number m_nInputChannels;
  icUInt16Number m_nOutputChannels;

  //Define base signature for extension purposes
  icSignature m_sigBaseLevel;
};


/**
****************************************************************************
* Class: CIccMpeUnknown
* 
* Purpose: Base Class for Process Elements
*****************************************************************************
*/
class CIccMpeUnknown : public CIccMultiProcessElement
{
public:
  CIccMpeUnknown();
  CIccMpeUnknown(const CIccMpeUnknown &elem);
  CIccMpeUnknown &operator=(const CIccMpeUnknown &elem);
  virtual CIccMultiProcessElement *NewCopy() const { return new CIccMpeUnknown(*this);}
  virtual ~CIccMpeUnknown();

  virtual icElemTypeSignature GetType() const { return m_sig; }
  virtual const icChar *GetClassName() const { return "CIccMpeentUnknown"; }

  virtual bool IsSupported() { return false; }

  virtual void Describe(std::string &sDescription);

  bool SetDataSize(icUInt32Number nSize, bool bZeroData=true);
  icUInt8Number *GetData() { return m_pData; }

  virtual bool Read(icUInt32Number nSize, CIccIO *pIO);
  virtual bool Write(CIccIO *pIO);

  virtual bool Begin(icElemInterp nIterp=icElemInterpLinear, CIccTagMultiProcessElement *pMPE=NULL) { return false; }
  virtual void Apply(icFloatNumber *pDestPixel, const icFloatNumber *pSrcPixel) {}

  virtual icValidateStatus Validate(icTagSignature sig, std::string &sReport, const CIccTagMultiProcessElement* pMPE=NULL) const;

protected:
  icElemTypeSignature m_sig;
  icUInt32Number m_nReserved;
  icUInt16Number m_nInputChannels;
  icUInt16Number m_nOutputChannels;
  icUInt32Number m_nSize;
  icUInt8Number *m_pData;
};


/**
****************************************************************************
* Class: CIccDblPixelBuffer
* 
* Purpose: The general purpose pixel storage buffer for pixel apply
*****************************************************************************
*/
class CIccDblPixelBuffer
{
public:
  CIccDblPixelBuffer();
  CIccDblPixelBuffer(const CIccDblPixelBuffer &buf);
  CIccDblPixelBuffer &operator=(const CIccDblPixelBuffer &buf);
  virtual ~CIccDblPixelBuffer();

  void Clean();
  void Reset() { m_nLastNumChannels = 0; }
  
  void UpdateChannels(icUInt16Number nNumChannels) { 
    m_nLastNumChannels = nNumChannels;
    if (nNumChannels>m_nMaxChannels) 
      m_nMaxChannels=nNumChannels;
  }

  bool Begin();

  icUInt16Number GetMaxChannels() { return m_nMaxChannels; }
  icFloatNumber *GetSrcBuf() { return m_pixelBuf1; }
  icFloatNumber *GetDstBuf() { return m_pixelBuf2; }

  void Switch() { icFloatNumber *tmp; tmp=m_pixelBuf2; m_pixelBuf2=m_pixelBuf1; m_pixelBuf1=tmp; }

  icUInt16Number GetAvailChannels() { return m_nLastNumChannels & 0x7fff; }

protected:
  //For application
  icUInt16Number m_nMaxChannels;
  icUInt16Number m_nLastNumChannels;
  icFloatNumber *m_pixelBuf1;
  icFloatNumber *m_pixelBuf2;
};

/**
****************************************************************************
* Class: CIccTagMultiProcessElement
* 
* Purpose: A general purpose processing tag 
*****************************************************************************
*/
class CIccTagMultiProcessElement : public CIccTag
{
public:
  CIccTagMultiProcessElement(icUInt16Number nInputChannels=0, icUInt16Number nOutputChannels=0);
  CIccTagMultiProcessElement(const CIccTagMultiProcessElement &lut);
  CIccTagMultiProcessElement &operator=(const CIccTagMultiProcessElement &lut);
  virtual CIccTag *NewCopy() const { return new CIccTagMultiProcessElement(*this);}
  virtual ~CIccTagMultiProcessElement();

  virtual bool IsSupported();

  virtual icTagTypeSignature GetType() { return icSigMultiProcessElementType; }
  virtual const icChar *GetClassName() { return "CIccTagMultiProcessElement"; }

  virtual void Describe(std::string &sDescription);

  virtual bool Read(icUInt32Number size, CIccIO *pIO);
  virtual bool Write(CIccIO *pIO);

  virtual void Attach(CIccMultiProcessElement *pElement);

  CIccMultiProcessElement *GetElement(int nIndex);
  void DeleteElement(int nIndex);

  virtual bool Begin(icElemInterp nInterp=icElemInterpLinear);
  virtual void Apply(icFloatNumber *pDestPixel, const icFloatNumber *pSrcPixel);
  virtual icValidateStatus Validate(icTagSignature sig, std::string &sReport, const CIccProfile* pProfile=NULL) const;

  icUInt16Number NumInputChannels() const { return m_nInputChannels; }
  icUInt16Number NumOutputChannels() const { return m_nOutputChannels; }
 
protected:
  virtual void Clean();
  virtual void GetNextElemIterator(CIccMultiProcessElementList::iterator &itr);
  virtual icInt32Number ElementIndex(CIccMultiProcessElement *pElem);

  virtual CIccMultiProcessElementList::iterator GetFirstElem();
  virtual CIccMultiProcessElementList::iterator GetLastElem();

  icUInt16Number m_nInputChannels;
  icUInt16Number m_nOutputChannels;

  //List of processing elements
  CIccMultiProcessElementList *m_list;

  //Offsets of loaded elements
  icUInt32Number m_nProcElements;
  icPositionNumber *m_position;

  //Pixel data for Apply 
  CIccDblPixelBuffer m_applyBuf;
};


//CIccFloatTag support
#ifdef USESAMPLEICCNAMESPACE
}
#endif

#endif //_ICCTAGMPE_H