#ifndef CHARCODECONVERTER_H_
#define CHARCODECONVERTER_H_

/**
 * 文字コード変換クラス
 * 
 */
class CharCodeConverter
{
public:
    CharCodeConverter();
    ~CharCodeConverter();
    bool Initialize();
    void Finalize();

    /**
     * 文字 UTF-16 BE を Shift_JIS に変換します。
     * @param c Shift_JIS 文字コード
     * @return UTF-16 BE 文字コード
     */
    uint32_t UTF16BEtoSJIS(const uint32_t c);

    /**
     * 文字列 UTF-16 BE を Shift_JIS に変換します。
     * @param buffer 書き込み先バッファ
     * @param utf16str 変換元 UTF-16 BE 文字列
     * @return 書き込みへのポインタ
     */
    char* UTF16BEtoSJIS(char *buffer, const wchar_t *utf16str);

    /**
     * 文字 Shift_JIS を UTF-16 BE に変換します。
     * @param c UTF-16 BE 文字コード
     * @return Shift_JIS 文字コード
     */
    wchar_t SJIStoUTF16BE(const uint32_t c);

    /**
     * 文字列 Shift_JIS を UTF-16 BE に変換します。
     * @param buffer 書き込み先バッファ
     * @param sjis 変換元 Shift_JIS 文字列
     * @return 書き込みへのポインタ
     */
    wchar_t *SJIStoUTF16BE(wchar_t *buffer, const char *sjis);

    /**
     * 文字列 UTF-8 を UTF-16 BE に変換します。
     * @param buffer 書き込み先バッファ
     * @param utf8str 変換元 UTF-16 BE 文字列
     * @return 書き込みへのポインタ
     */
    wchar_t* UTF8toUTF16BE(wchar_t *buffer, const char *utf8str);

    /**
     * 文字列 UTF-8 を UTF-16 BE に変換します。
     * @param buffer 書き込み先バッファ
     * @param bufferCount 書き込み先バッファサイズ
     * @param utf8str 変換元 UTF-16 BE 文字列
     * @return 書き込みへのポインタ
     */
    wchar_t* UTF8toUTF16BE(wchar_t *buffer, int32_t bufferCount , const char *utf8str);

public:
    static const int32_t MAX_HASH_TABLE = 256;
    static const uint32_t CODE_TABLE_SIZE = 3647;

private:
    struct CodeData
    {
        int32_t mbchar;
        int32_t index;
        CodeData *pNext;

        CodeData()
            : mbchar(0)
            , pNext(NULL)
        {}
    };

private:
    CodeData* m_HashTableToSJIS[MAX_HASH_TABLE];
    CodeData m_DataToSJIS[CODE_TABLE_SIZE];
    CodeData* m_HashTableToUTF16[MAX_HASH_TABLE];
    CodeData m_DataToUTF16[CODE_TABLE_SIZE];
};

#endif // CHARCODECONVERTER_H_
