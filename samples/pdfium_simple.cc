// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "public/fpdfview.h"

int main() {
  FILE *fp;
  fp=fopen("bmp.raw", "w");
  FPDF_DOCUMENT doc = FPDF_LoadDocument("sample.pdf", nullptr);
  int pagecount = FPDF_GetPageCount(doc);
  printf("pages: %d\n", pagecount);
  printf("%s\n", "doc loaded.");
  FPDF_PAGE page = FPDF_LoadPage(doc, 0);
  printf("%s\n", "page loaded.");
  int width = (int)FPDF_GetPageWidth(page);
  int height = (int)FPDF_GetPageHeight(page);
  FPDF_BITMAP bmp = FPDFBitmap_Create(width, height, 0);
  FPDF_RenderPageBitmap(bmp, page, 0, 0, width, height, 0, 0);
  void* buf = FPDFBitmap_GetBuffer(bmp);
  fwrite(buf, 4, width*height, fp);
  fclose(fp);
  return 0;
}
