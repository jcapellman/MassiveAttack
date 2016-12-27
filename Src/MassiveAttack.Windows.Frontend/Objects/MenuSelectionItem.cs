using System.Windows;

namespace MassiveAttack.Windows.Frontend.Objects
{
    public class MenuSelectionItem
    {
        public string MenuText { get; set; }

        public Window WindowInstance { get; set; }

        public bool IsEnabled { get; set; }
    }
}