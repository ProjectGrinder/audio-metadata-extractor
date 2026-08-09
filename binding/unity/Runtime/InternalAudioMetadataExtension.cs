using System;
using System.Runtime.InteropServices;

namespace Takayama.AudioMetadataExtension.Runtime
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct InternalAudioProperties
    {
        public double Duration;
        public int Bitrate;
        public int SampleRate;
        public int Channels;
    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct InternalImageData
    {
        public IntPtr ImageDataPtr;
        public IntPtr MimePtr;
        public uint ImageSize;
        public uint MimeSize;
    }
    
    internal static class InternalAudioMetadata
    {
        private const string LibName = "audio_metadata_extension-native";

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void InternalMetadataCallback(
            [MarshalAs(UnmanagedType.LPUTF8Str)] string key,
            [MarshalAs(UnmanagedType.LPUTF8Str)] string value,
            IntPtr userData
        );

        [DllImport(LibName, EntryPoint = "extract_metadata", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ExtractMetadata(
            [In] byte[] byteData,
            uint size,
            InternalMetadataCallback callback,
            IntPtr userData
        );

        [DllImport(LibName, EntryPoint = "extract_audio_properties", CallingConvention = CallingConvention.Cdecl)]
        internal static extern InternalAudioProperties ExtractAudioProperties(
            [In] byte[] byteData,
            uint size
        );

        [DllImport(LibName, EntryPoint = "extract_image", CallingConvention = CallingConvention.Cdecl)]
        internal static extern InternalImageData ExtractImage(
            [In] byte[] byteData,
            uint size
        );

        [DllImport(LibName, EntryPoint = "free_image", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void FreeImage(ref InternalImageData image);
    }
}