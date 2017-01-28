using System;

namespace MassiveAttack.MasterServer.WebAPI.Implementations.Redis.Objects
{
    public class GameServerItem
    {
        public string ServerTitle { get; set; }

        public string CurrentMap { get; set; }

        public int NumPlayers { get; set; }

        public int MaxPlayers { get; set; }

        public DateTimeOffset LastPingBack { get; set; }

        public string ServerID { get; set; }
    }
}