namespace MassiveAttack.Common.Library.Objects.WebAPI.GameServers
{
    public class GameServerPingBackRequestItem
    {
        // This can be null if you just registering
        public string ServerID { get; set; }

        public string ServerTitle { get; set; }

        public string CurrentMap { get; set; }

        public int NumPlayers { get; set; }

        public int MaxPlayers { get; set; }
    }
}