// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FXGE_PS_FX_PS_DEVICE_H_
#define CORE_FXGE_PS_FX_PS_DEVICE_H_

#include <memory>
#include <vector>

#include "core/fxge/include/fx_ge.h"
#include "core/fxge/include/ifx_renderdevicedriver.h"

class IFX_PSOutput {
 public:
  virtual void Release() = 0;
  virtual void OutputPS(const FX_CHAR* str, int len) = 0;
 protected:
  virtual ~IFX_PSOutput() {}
};
class CPSFont;
class CFX_PSRenderer : public IFX_RenderDeviceDriver {
 public:
  CFX_PSRenderer();
  ~CFX_PSRenderer();
  void Init(IFX_PSOutput* pOutput,
            int ps_level,
            int width,
            int height,
            FX_BOOL bCmykOutput);
  FX_BOOL StartRendering();
  void EndRendering();
  void SaveState();
  void RestoreState(FX_BOOL bKeepSaved = FALSE);
  FX_BOOL SetClip_PathFill(const CFX_PathData* pPathData,
                        const CFX_Matrix* pObject2Device,
                        int fill_mode);
  FX_BOOL SetClip_PathStroke(const CFX_PathData* pPathData,
                          const CFX_Matrix* pObject2Device,
                          const CFX_GraphStateData* pGraphState);
  FX_RECT GetClipBox() { return m_ClipBox; }
  FX_BOOL DrawPath(const CFX_PathData* pPathData,
                   const CFX_Matrix* pObject2Device,
                   const CFX_GraphStateData* pGraphState,
                   uint32_t fill_color,
                   uint32_t stroke_color,
                   int fill_mode,
                   int alpha_flag = 0,
                   void* pIccTransform = NULL);
  FX_BOOL SetDIBits(const CFX_DIBSource* pBitmap,
                    uint32_t color,
                    int dest_left,
                    int dest_top,
                    int alpha_flag = 0,
                    void* pIccTransform = NULL);
  FX_BOOL StretchDIBits(const CFX_DIBSource* pBitmap,
                        uint32_t color,
                        int dest_left,
                        int dest_top,
                        int dest_width,
                        int dest_height,
                        uint32_t flags,
                        int alpha_flag = 0,
                        void* pIccTransform = NULL);
  FX_BOOL DrawDIBits(const CFX_DIBSource* pBitmap,
                     uint32_t color,
                     const CFX_Matrix* pMatrix,
                     uint32_t flags,
                     int alpha_flag = 0,
                     void* pIccTransform = NULL);
  FX_BOOL DrawText(int nChars,
                   const FXTEXT_CHARPOS* pCharPos,
                   CFX_Font* pFont,
                   CFX_FontCache* pCache,
                   const CFX_Matrix* pObject2Device,
                   FX_FLOAT font_size,
                   uint32_t color,
                   int alpha_flag = 0,
                   void* pIccTransform = NULL);
 private:
  IFX_PSOutput* m_pOutput;
  int m_PSLevel;
  CFX_GraphStateData m_CurGraphState = {};
  FX_BOOL m_bGraphStateSet;
  FX_BOOL m_bCmykOutput;
  FX_BOOL m_bColorSet;
  uint32_t m_LastColor;
  FX_RECT m_ClipBox;
  CFX_ArrayTemplate<CPSFont*> m_PSFontList;
  CFX_ArrayTemplate<FX_RECT> m_ClipBoxStack;
  FX_BOOL m_bInited;
  void OutputPath(const CFX_PathData* pPathData,
                  const CFX_Matrix* pObject2Device);
  void SetGraphState(const CFX_GraphStateData* pGraphState);
  void SetColor(uint32_t color, int alpha_flag, void* pIccTransform);
  void FindPSFontGlyph(CFX_FaceCache* pFaceCache,
                       CFX_Font* pFont,
                       const FXTEXT_CHARPOS& charpos,
                       int& ps_fontnum,
                       int& ps_glyphindex);
  void WritePSBinary(const uint8_t* data, int len);
};
#endif
