using System;
using System.IO;

using MassiveAttack.Common.Library.Objects.Common;

using Newtonsoft.Json;

namespace MassiveAttack.Common.Library.PlatformAbstractions
{
    public abstract class BaseFileIO
    {
        protected abstract string GetRootDirectory();

        public ReturnSet<T> ReadJOSNFile<T>(string fileName)
        {
            try
            {
                var fullPath = Path.Combine(GetRootDirectory(), fileName);

                if (!File.Exists(fullPath))
                {
                    throw new Exception($"{fullPath} was not found");
                }

                var str = File.ReadAllText(fullPath);

                return new ReturnSet<T>(JsonConvert.DeserializeObject<T>(str));
            }
            catch (Exception ex)
            {
                return new ReturnSet<T>(ex);
            }
        }

        public ReturnSet<bool> WriteJOSNFile<T>(string fileName, T objectValue)
        {
            try
            {
                var fullPath = Path.Combine(GetRootDirectory(), fileName);

                File.WriteAllText(fullPath, JsonConvert.SerializeObject(objectValue));

                return new ReturnSet<bool>(true);
            }
            catch (Exception ex)
            {
                return new ReturnSet<bool>(ex);
            }
        }
    }
}