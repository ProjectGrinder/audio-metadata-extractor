using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Takayama.AudioMetadataExtension.Runtime
{
    public sealed class NativeImageBuffer : IDisposable
    {
        private InternalImageData _rawImage;
        private bool _disposed;

        public bool IsValid => !_disposed && _rawImage.ImageDataPtr != IntPtr.Zero && _rawImage.ImageSize > 0;
        public uint Size => _disposed ? 0 : _rawImage.ImageSize;
        public string MimeType { get; }

        internal NativeImageBuffer(InternalImageData rawImage)
        {
            _rawImage = rawImage;

            if (rawImage.MimePtr != IntPtr.Zero && rawImage.MimeSize > 0)
            {
#if NETSTANDARD2_1_OR_GREATER || NETCOREAPP1_0_OR_GREATER
                MimeType = Marshal.PtrToStringUTF8(rawImage.MimePtr, (int)rawImage.MimeSize);
#else
                byte[] mimeBytes = new byte[rawImage.MimeSize];
                Marshal.Copy(rawImage.MimePtr, mimeBytes, 0, (int)rawImage.MimeSize);
                MimeType = Encoding.UTF8.GetString(mimeBytes);
#endif
            }
        }

        public unsafe ReadOnlySpan<byte> Span
        {
            get
            {
                if (!IsValid)
                    return ReadOnlySpan<byte>.Empty;

                return new ReadOnlySpan<byte>((void*)_rawImage.ImageDataPtr, (int)_rawImage.ImageSize);
            }
        }
        
        public byte[] ToArray()
        {
            if (!IsValid)
                return Array.Empty<byte>();

            byte[] managedArray = new byte[_rawImage.ImageSize];
            Marshal.Copy(_rawImage.ImageDataPtr, managedArray, 0, (int)_rawImage.ImageSize);
            return managedArray;
        }

        public void Dispose()
        {
            if (!_disposed)
            {
                _disposed = true;
                if (_rawImage.ImageDataPtr != IntPtr.Zero)
                {
                    InternalAudioMetadata.FreeImage(ref _rawImage);
                }
            }
            GC.SuppressFinalize(this);
        }

        ~NativeImageBuffer()
        {
            Dispose();
        }
    }
}