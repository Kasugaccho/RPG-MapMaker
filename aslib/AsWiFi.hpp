//     ----------     ----------     ----------     ----------     ----------
//
//                              AsLib - Asライブラリ
//
//                    制作者: がっちょ (wanotaitei@gmail.com)
//
//     ----------     ----------     ----------     ----------     ----------


namespace AsLib
{

#if defined(ASLIB_INCLUDE_DL) //DxLib

#if defined(__ANDROID__)

	//<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />追加あり
	inline int32_t asWifi()
	{
		//return int32_t(DxLib::GetWifiSignalLevel());
		return 0;
}
#endif

#elif defined(ASLIB_INCLUDE_S3) //Siv3D

#else //Console

#endif

}
