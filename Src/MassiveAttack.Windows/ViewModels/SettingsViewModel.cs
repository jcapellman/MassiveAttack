using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Enums;
using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Settings;
using MassiveAttack.Common.Library.WebAPIHandlers;

using Vulkan;

namespace MassiveAttack.Windows.ViewModels
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

        private ObservableCollection<PhysicalDeviceProperties> _devices;

        public ObservableCollection<PhysicalDeviceProperties> Devices
        {
            get { return _devices; }
            set
            {
                _devices = value;
                OnPropertyChanged();
            }
        }

        private PhysicalDeviceProperties _selectedDevice;

        public PhysicalDeviceProperties SelectedDevice
        {
            get { return _selectedDevice; }
            set
            {
                _selectedDevice = value;
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

        public async void InitializeSettings()
        {
            var settingsHandler = new SettingsHandler(App.HandlerWrapper);

            var result = await settingsHandler.GetSettings();

            if (!result.HasError)
            {
                Settings = result.ObjectValue.SettingItem;
            }

            Devices = new ObservableCollection<PhysicalDeviceProperties>();

            var devices = new ObservableCollection<PhysicalDevice>(App.instance.EnumeratePhysicalDevices());

            foreach (var device in devices)
            {
                var props = device.GetProperties();

                if (props.DeviceId == Settings.DeviceID)
                {
                    SelectedDevice = props;
                }

                Devices.Add(props);
            }

            if (SelectedDevice == null)
            {
                SelectedDevice = Devices.FirstOrDefault();
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