namespace MassiveAttack.CommonLibrary.Objects.WebAPI.HighScore {

    public class HighScoreListingResponseItem : BaseListingResponseItem {
        public string PlayerName { get; set; }
        
        public int Score { get; set; }
    }
}