using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Enums;
using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Settings;
using MassiveAttack.Common.Library.WebAPIHandlers;

namespace MassiveAttack.Windows.Frontend.ViewModels
{
    public class SettingsViewModel : BaseViewModel
    {
        private SettingsItem _settings;

        public SettingsItem Settings
        {
            get { return _settings; }
            set
            {
                _settings = value;
                OnPropertyChanged();
            }
        }

        private ObservableCollection<string> _renderers;

        public ObservableCollection<string> Renderers
        {
            get { return _renderers; }
            set
            {
                _renderers = value;
                OnPropertyChanged();
            }
        }

        private string _selectedRenderer;

        public string SelectedRenderer
        {
            get { return _selectedRenderer; }
            set
            {
                _selectedRenderer = value;
                OnPropertyChanged();
            }
        }

        private List<string> _TextureDetails;

        public List<string> TextureDetails
        {
            get { return _TextureDetails; }
            set
            {
                _TextureDetails = value;
                OnPropertyChanged();
            }
        }

        private string _selectedTextureDetail;

        public string SelectedTextureDetail
        {
            get { return _selectedTextureDetail; }
            set
            {
                _selectedTextureDetail = value;
                OnPropertyChanged();
            }
        }

        public SettingsViewModel()
        {
            Settings = new SettingsItem
            {
                BPP = 16,
                ResolutionX = 1024,
                ResolutionY = 768,
                TextureDetail = TEXTURE_DETAIL.INSANE
            };
        }

        [DllImport("MassiveAttack.Client.Engine.dll")]
        public static extern string GetAvailableGfxRenderers();

        public static List<string> intPtrToListString(IntPtr[] pointers)
        {
            var list = new List<string>();

            foreach (var pointer in pointers)
            {
                list.Add(Marshal.PtrToStringAnsi(pointer));
            }

            return list;
        }

        public async void InitializeSettings()
        {
            var settingsHandler = new SettingsHandler(App.HandlerWrapper);

            var result = await settingsHandler.GetSettings();

            if (!result.HasError)
            {
                Settings = result.ObjectValue.SettingItem;
            }

                var temp = GetAvailableGfxRenderers();

            Renderers = new ObservableCollection<string>();
            
            if (SelectedRenderer == null)
            {
                SelectedRenderer = Renderers.FirstOrDefault();
            }

            TextureDetails = Enum.GetNames(typeof (TEXTURE_DETAIL)).ToList();

            SelectedTextureDetail = Settings.TextureDetail.ToString();
        }

        public async Task<ReturnSet<bool>> SaveSettings()
        {
            var requestItem = new SettingsRequestItem
            {
                SettingItem = Settings
            };

            var settingsHandler = new SettingsHandler(App.HandlerWrapper);

            return await settingsHandler.UpdateSettings(requestItem);
        }
    }
}