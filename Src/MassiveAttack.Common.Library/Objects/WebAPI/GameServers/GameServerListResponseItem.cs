using System;

namespace MassiveAttack.Common.Library.Objects.WebAPI.GameServers
{
    public class GameServerListResponseItem
    {
        public string ServerID { get; set; }

        public string ServerTitle { get; set; }

        public string CurrentMap { get; set; }

        public int NumPlayers { get; set; }

        public int MaxPlayers { get; set; }
    }
}