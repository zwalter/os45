//
// lresizer.h
//
// lresizer

#if !defined(__LRESIZER__H__)
#define __LRESIZER__H__

// Our GUID. Generated by the wizard to be unique.
// {16d181a8-35c9-4054-ae1f-6d578b796794}
// {19AE8C00-01AF-43c1-B9D9-C039B24BE984}
static const GUID CLSID_StretchDIBitsResizer = 
{ 0x16d181a8, 0x35c9, 0x4054, { 0xae, 0x1f, 0x6d, 0x57, 0x8b, 0x79, 0x67, 0x94 } };
//DEFINE_GUID(CLSID_StretchDIBitsResizer,
//            0x16d181a8, 0x35c9, 0x4054, 0xae, 0x1f, 0x6d, 0x57, 0x8b, 0x79, 0x67, 0x94);

#ifndef __STREAMS__
#include "streams.h" // DS BaseClasses: CTransformFilter
#endif

#include <qedit.h>

//
// Clresizer
//
class CStretchDIBitsResizer : public CTransformFilter, IResize
{
public:
   
   // filter object registration information
   static const AMOVIESETUP_FILTER sudFilter;
   static const AMOVIESETUP_MEDIATYPE sudInputTypes[];
   static const AMOVIESETUP_MEDIATYPE sudOutputTypes[];
   static const AMOVIESETUP_PIN sudPins[];
   
   // called to create the COM filter oject
   static CUnknown *WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);
   
   virtual ~CStretchDIBitsResizer();
   
   DECLARE_IUNKNOWN;
   virtual HRESULT __stdcall NonDelegatingQueryInterface(REFIID riid, LPVOID *ppv);
   
   // CTransformFilter overridables   
   virtual HRESULT CheckInputType(const CMediaType *mtIn);
   virtual HRESULT CheckTransform(const CMediaType *mtIn, const CMediaType *mtOut);
   virtual HRESULT DecideBufferSize(IMemAllocator *pAlloc, ALLOCATOR_PROPERTIES *ppropInputRequest);
   virtual HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);
   virtual HRESULT Transform(IMediaSample *pIn, IMediaSample *pOut);
   
   // IResize
   virtual HRESULT STDMETHODCALLTYPE get_InputSize(int *piHeight, int *piWidth);
   virtual HRESULT STDMETHODCALLTYPE get_MediaType(AM_MEDIA_TYPE *pmt);
   virtual HRESULT STDMETHODCALLTYPE get_Size(int *piHeight, int *piWidth, long *pFlag);
   virtual HRESULT STDMETHODCALLTYPE put_MediaType(const AM_MEDIA_TYPE *pmt);
   virtual HRESULT STDMETHODCALLTYPE put_Size(int Height, int Width, long Flags);

private:
   
   // Constructor - just calls the base class constructor
   CStretchDIBitsResizer(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
   
   // return the number of pins this filter has
   //virtual int           GetPinCount();
   
   // pointer to a pin.
   //virtual CBasePin* GetPin(int n);
   // use to serialize access to filter interface methods.
   //CCritSec m_FilterLock;
   
   // CBaseFilter derived objects cannot be copied
   CStretchDIBitsResizer(const CStretchDIBitsResizer&);
   CStretchDIBitsResizer& operator=(const CStretchDIBitsResizer&);

   long       m_nStretchMode;

   CMediaType m_mtIn;
   CMediaType m_mtOut;
   bool       m_outTypeInitialized;
   bool       m_outTypeHasChanged;

   HBITMAP    m_hInBitmap;
   HDC        m_hInDC;
   LPVOID     m_pInBits;
   int        m_inBitsSize;
   HBITMAP    m_hOutBitmap;
   HDC        m_hOutDC;
   LPVOID     m_pOutBits;
   int        m_outBitsSize;

   int m_destX;
   int m_destY;
   int m_destWidth;
   int m_destHeight;
   int m_srcX;
   int m_srcY;
   int m_srcWidth;
   int m_srcHeight;

   void FreeResources();
   void CalculateStretchParameters();
};

#endif // __LRESIZER__H__