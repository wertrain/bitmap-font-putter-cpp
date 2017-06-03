#ifndef CHARCODECONVERTER_H_
#define CHARCODECONVERTER_H_

/**
 * 文字コードを変換をします。
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
     * 文字 UTF-16 BE を SJIS に変換します。
     * 
     */
    uint32_t UTF16BEtoSJIS(const uint32_t c);

    /**
     * 文字列 UTF-16 BE を SJIS に変換します。
     * 
     */
    char* UTF16BEtoSJIS(char *buffer, const wchar_t *utf16str);

    /**
     * 文字 SJIS を UTF-16 BE に変換します。
     * 
     */
    wchar_t SJIStoUTF16BE(const uint32_t c);

    /**
     * 文字列 SJIS を UTF-16 BE に変換します。
     * 
     */
    wchar_t *SJIStoUTF16BE(wchar_t *buffer, const char *sjis);

    /**
     * 文字列 UTF-8 を UTF-16 BE に変換します。
     * 
     */
    wchar_t* UTF8toUTF16BE(wchar_t *buffer, const char *utf8str);

    /**
     * 文字列 UTF-8 を UTF-16 BE に変換します。
     * 
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
