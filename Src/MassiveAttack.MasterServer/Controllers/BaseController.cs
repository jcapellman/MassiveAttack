﻿using MassiveAttack.MasterServer.Objects;

using Microsoft.AspNetCore.Mvc;

namespace MassiveAttack.MasterServer.Controllers
{
    [Route("api/[controller]")]
    public class BaseController : Controller
    {
        protected GlobalSettings gSettings;
    }
}