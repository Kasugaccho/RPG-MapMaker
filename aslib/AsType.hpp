//     ----------     ----------     ----------     ----------     ----------
//
//                              AsLib - AsCu
//
//                    §ìÒ: ªÁ¿å (wanotaitei@gmail.com)
//
//     ----------     ----------     ----------     ----------     ----------


namespace AsLib
{
#if defined(ASLIB_INCLUDE_DL) //DxLib
	//`ææn
	using OriginatorTexture = int;
	//CPUæn
	using OriginatorImage = int;
	//å¹ºn
	using OriginatorBGM = int;
	//¹ºn
	using OriginatorSE = int;
	//®æn
	using OriginatorMovie = int;
	//¶n
	using OriginatorFont = int;
#elif defined(ASLIB_INCLUDE_S3) //Siv3D
	//`ææn
	using OriginatorTexture = s3d::Texture;
	//CPUæn
	using OriginatorImage = int32_t;
	//å¹ºn
	using OriginatorBGM = s3d::Audio;
	//¹ºn
	using OriginatorSE = int32_t;
	//®æn
	using OriginatorMovie = int32_t;
	//¶n
	using OriginatorFont = s3d::Font;
//#define TEX_INIT asTexture(U"a.png")
#elif defined(ASLIB_INCLUDE_OF)
	//`ææn
	using OriginatorTexture = ofImage;
	//CPUæn
	using OriginatorImage = int32_t;
	//å¹ºn
	using OriginatorBGM = int32_t;
	//¹ºn
	using OriginatorSE = int32_t;
	//®æn
	using OriginatorMovie = int32_t;
	//¶n
	using OriginatorFont = ofTrueTypeFont;
#elif defined(ASLIB_INCLUDE_TP)
	//`ææn
	using OriginatorTexture = int32_t;
	//CPUæn
	using OriginatorImage = int32_t;
	//å¹ºn
	using OriginatorBGM = int32_t;
	//¹ºn
	using OriginatorSE = int32_t;
	//®æn
	using OriginatorMovie = int32_t;
	//¶n
	using OriginatorFont = int32_t;
#else //Console
	//`ææn
	using OriginatorTexture = int32_t;
	//CPUæn
	using OriginatorImage = int32_t;
	//å¹ºn
	using OriginatorBGM = int32_t;
	//¹ºn
	using OriginatorSE = int32_t;
	//®æn
	using OriginatorMovie = int32_t;
	//¶n
	using OriginatorFont = int32_t;
#endif
}
