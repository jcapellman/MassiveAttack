using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Settings;

namespace MassiveAttack.Common.Library.WebAPIHandlers
{
    public class SettingsHandler : BaseWebAPIHandler
    {
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

                throw new Exception("No internet connection");
            }
            catch (Exception ex)
            {
                return new ReturnSet<SettingsResponseItem>(ex);
            }
        } 
    }
}