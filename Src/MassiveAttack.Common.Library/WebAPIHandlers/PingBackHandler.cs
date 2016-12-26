using System.Threading.Tasks;
using MassiveAttack.Common.Library.Objects.Common;

namespace MassiveAttack.Common.Library.WebAPIHandlers
{
    public class PingBackHandler : BaseWebAPIHandler
    {
        public PingBackHandler(HandlerConstructorItem constructorItem) : base(constructorItem)
        {
        }

        public async Task<bool> CheckServiceStatus() => await GetAsync<bool>("ServiceStatus");
    }
}