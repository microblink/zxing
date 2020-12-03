/*
 *
 *  Copyright 2010 ZXing authors All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __DEFS_H__
#define __DEFS_H__


#define kZXING_LIBSUPPORT					@"dflts_zxing_libsupport"
#define KZXING_MIRROR_VIDEO					@"dflts_zxing_mirrorvideo"
#define KZXING_SOUND_ON_RESULT				@"dflts_zxing_soundonresult"
#define kZXING_VIDEOSOURCENAME				@"dflts_zxing_videosourcename"
#define kVIDEOSOURCETITLE					@"dflts_videosourcetitle"

#define kIMAGESOURCESELECTIONPOPUPTITLE		@"Select video source"
#define kIMAGESOURCESELECTIONRESCANTITLE	@"ReScan for video Sources"
#define kIMAGESOURCESELECTIONDISCONNECT		@"Disconnect video source"

#define kCAPTURESUCCESSSOUNDFILENAME		@"beepbeep.aif"


#define kBACKGROUNDCOLOR		CGColorCreateGenericRGB(0.4,0.4,0.4,1.0)
#define kWHITEHAZECOLOR		CGColorCreateGenericRGB(0.4,0.4,0.4,1.0)

#define kLEFTVIDEOEASE		8.0
#define kTOPVIDEOEASE		8.0
#define kWIDTHVIDEOEASE		(kLEFTVIDEOEASE*2)
#define kHEIGHTVIDEOEASE	(kTOPVIDEOEASE*2)

#define kZXINGWEBURL		@"http://code.google.com/p/zxing/"

#define kCANCELTITLE		@"Cancel"
#define kCAPTURETITLE		@"Capture"

#define kVIDEOSOURCEOFFSET					1001
#define kBLANKSTR							@""
#define kNO_SUCH_MENU_ITEM					-1

#endif // __DEFS_H__
