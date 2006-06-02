/*
    File:       IccTagDlg.cpp

    Contains:   implementation of the CIccTagDlg class

    Version:    V1

    Copyright:  � see below
*/

/*
 * The ICC Software License, Version 0.1
 *
 *
 * Copyright (c) 2003-2006 The International Color Consortium. All rights 
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
 * 4. The names "ICC" and "The International Color Consortium" must
 *    not be used to imply that the ICC organization endorses or
 *    promotes products derived from this software without prior
 *    written permission. For written permission, please see
 *    <http://www.color.org/>.
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
// -Initial implementation by Max Derhak 5-15-2003
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProfileDump.h"
#include "IccTagDlg.h"
#include "IccUtil.h"
#include "IccTag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIccTagDlg dialog


CIccTagDlg::CIccTagDlg(CWnd* pParent /*=NULL*/, CIccProfile *pIcc /*=NULL*/,
                       icTagSignature sig/*=icMaxEnumTag*/, CIccTag *pTag /*=NULL*/)
  : CDialog(CIccTagDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CIccTagDlg)
  //}}AFX_DATA_INIT

  m_pIcc = pIcc;
  m_sigTag = sig;
  m_pTag = pTag;

  CIccInfo Fmt;

  m_sTagSignature = Fmt.GetTagSigName(sig);
  if (pTag->IsArrayType()) {
    m_sTagType = "Array of ";
  }
  else {
    m_sTagType.Empty();
  }
  m_sTagType += Fmt.GetTagTypeSigName(pTag->GetType());

  std::string desc;
  BeginWaitCursor();
  pTag->Describe(desc);
  m_sTagData = desc.c_str();
  EndWaitCursor();
}


void CIccTagDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CIccTagDlg)
  DDX_Text(pDX, IDC_TAG_SIGNATURE, m_sTagSignature);
  DDX_Text(pDX, IDC_TAG_TYPE, m_sTagType);
  DDX_Text(pDX, IDC_TAG_DATA, m_sTagData);
  //}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CIccTagDlg, CDialog)
  //{{AFX_MSG_MAP(CIccTagDlg)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIccTagDlg message handlers

BOOL CIccTagDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  m_FixedFont.CreatePointFont(80, "Terminal");

  CEdit *pData = (CEdit*)GetDlgItem(IDC_TAG_DATA);

  int start, end;

  pData->SetFont(&m_FixedFont);
  pData->GetSel(start, end);
  // TODO: Add extra initialization here
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}
