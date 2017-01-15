using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Enums;
using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Settings;
using MassiveAttack.Common.Library.WebAPIHandlers;
using MassiveAttack.Windows.Frontend.Common;
using Newtonsoft.Json;

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
                XRes = 1024,
                YRes = 768,
                TextureDetail = TEXTURE_DETAIL.INSANE
            };
        }        

        public async void InitializeSettings()
        {
            var settingsHandler = new SettingsHandler(App.HandlerWrapper);

            var result = await settingsHandler.GetSettings();

            if (!result.HasError)
            {
                Settings = result.ObjectValue.SettingItem;
            }

            Renderers = new ObservableCollection<string>
            {
                "OpenGL 1.1"
            };
            
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

            File.WriteAllText(Constants.ConfigName, Settings.ToSettingFileFormat());

            return await settingsHandler.UpdateSettings(requestItem);
        }
    }
}