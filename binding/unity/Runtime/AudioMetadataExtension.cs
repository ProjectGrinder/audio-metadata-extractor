using System;
using System.Collections.Generic;

namespace Takayama.AudioMetadataExtension.Runtime {
    public readonly struct AudioProperties
    {
        public double Duration { get; }
        public int Bitrate { get; }
        public int SampleRate { get; }
        public int Channels { get; }

        internal AudioProperties(InternalAudioProperties raw)
        {
            Duration = raw.Duration;
            Bitrate = raw.Bitrate;
            SampleRate = raw.SampleRate;
            Channels = raw.Channels;
        }
    }
    
    public static class AudioMetadata
    {
        public static AudioProperties ExtractAudioProperties(byte[] audioBytes)
        {
            if (audioBytes == null || audioBytes.Length == 0)
                throw new ArgumentException("Audio byte buffer cannot be null or empty.", nameof(audioBytes));

            var rawProps =
                InternalAudioMetadata.ExtractAudioProperties(audioBytes, (uint)audioBytes.Length);
            return new AudioProperties(rawProps);
        }

        public static Dictionary<string, string> ExtractMetadata(byte[] audioBytes)
        {
            if (audioBytes == null || audioBytes.Length == 0)
                throw new ArgumentException("Audio byte buffer cannot be null or empty.", nameof(audioBytes));

            var metadata = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);

            void Cb(string key, string value, IntPtr userData)
            {
                if (!string.IsNullOrEmpty(key) && value != null)
                {
                    metadata[key] = value;
                }
            }

            InternalAudioMetadata.ExtractMetadata(audioBytes, (uint)audioBytes.Length, Cb,
                IntPtr.Zero);
            return metadata;
        }

        public static NativeImageBuffer ExtractImage(byte[] audioBytes)
        {
            if (audioBytes == null || audioBytes.Length == 0)
                return new NativeImageBuffer(default);

            var rawImage =
                InternalAudioMetadata.ExtractImage(audioBytes, (uint)audioBytes.Length);
            return new NativeImageBuffer(rawImage);
        }
    }
}