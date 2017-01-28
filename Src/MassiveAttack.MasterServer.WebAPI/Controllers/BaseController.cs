using MassiveAttack.MasterServer.WebAPI.Objects;

using Microsoft.AspNetCore.Mvc;

namespace MassiveAttack.MasterServer.WebAPI.Controllers
{
    [Route("api/[controller]")]
    public class BaseController : Controller
    {
        protected GlobalSettings gSettings;
    }
}