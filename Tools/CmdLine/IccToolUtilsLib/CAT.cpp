/*
    File:       CLUT.cpp

    Contains:   part of iccCreateCLUTInputProfile command-line tool:
                chromatic adaptation transforms

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
// -Initial implementation by Joseph Goldstone spring 2006
//
//////////////////////////////////////////////////////////////////////

#include "CAT.h"
#include "IccUtil.h"

void
CAT::Apply(icFloatNumber * const product, const icFloatNumber * const multiplicand) const
{
    product[0] = m_CAT[0] * multiplicand[0] + m_CAT[1] * multiplicand[1] + m_CAT[2] * multiplicand[2];
    product[1] = m_CAT[3] * multiplicand[0] + m_CAT[4] * multiplicand[1] + m_CAT[5] * multiplicand[2];
    product[2] = m_CAT[6] * multiplicand[0] + m_CAT[7] * multiplicand[1] + m_CAT[8] * multiplicand[2];
}

CIccTagS15Fixed16*
CAT::makeChromaticAdaptationTag() const
{
    CIccTagS15Fixed16* tag = new CIccTagS15Fixed16(9);
    for (unsigned int i = 0; i < 9; ++i)
        (*tag)[i] = icDtoF(m_CAT[i]);
    return tag;
}