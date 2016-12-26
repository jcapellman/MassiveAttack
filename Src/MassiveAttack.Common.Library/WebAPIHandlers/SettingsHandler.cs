using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Settings;

namespace MassiveAttack.Common.Library.WebAPIHandlers
{
    public class SettingsHandler : BaseWebAPIHandler
    {
        private const string JSONFILE = "settings.json";

        public SettingsHandler(HandlerConstructorItem constructorItem) : base(constructorItem)
        {
        }

        public async Task<ReturnSet<SettingsResponseItem>> GetSettings()
        {
            try
            {
                if (IsOnline)
                {
                    return await GetAsync<ReturnSet<SettingsResponseItem>>("Settings");
                }

                var localFile = Wrapper.FileIO.ReadJOSNFile<SettingsResponseItem>(JSONFILE);

                if (localFile.HasError)
                {
                    throw new Exception("No connectivity and no local copy of Settings");
                }

                return new ReturnSet<SettingsResponseItem>(localFile.ObjectValue);
            }
            catch (Exception ex)
            {
                return new ReturnSet<SettingsResponseItem>(ex);
            }
        }

        public async Task<ReturnSet<bool>> UpdateSettings(SettingsRequestItem requestItem)
        {
            return await PostAsync<SettingsRequestItem, ReturnSet<bool>>("Settings", requestItem);
        }
    }
}