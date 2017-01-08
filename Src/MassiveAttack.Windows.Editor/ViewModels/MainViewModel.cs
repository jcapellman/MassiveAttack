using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Windows;
using MassiveAttack.Windows.Editor.Common;

namespace MassiveAttack.Windows.Editor.ViewModels
{
    public class MainViewModel : BaseViewModel
    {
        #region TEXTURES
        public class TEXTURE_DB_ITEM
        {
            public int ID { get; set; }

            public string FileName { get; set; }
        }

        private ObservableCollection<TEXTURE_DB_ITEM> _textures;

        public ObservableCollection<TEXTURE_DB_ITEM> Textures
        {
            get { return _textures; }
            set { _textures = value; OnPropertyChanged(); }
        }
        #endregion

        public class LEVELGEOMETRY
        {
            public int TextureID { get; set; }

            public int Scale { get; set; }

            public float X1 { get; set; }

            public float X2 { get; set; }

            public float X3 { get; set; }

            public float X4 { get; set; }

            public float Y1 { get; set; }

            public float Y2 { get; set; }

            public float Y3 { get; set; }

            public float Y4 { get; set; }

            public float Z1 { get; set; }

            public float Z2 { get; set; }

            public float Z3 { get; set; }

            public float Z4 { get; set; }
        }

        public MainViewModel()
        {
            LoadTextures();
        }

        private void LoadTextures()
        {
            Textures = new ObservableCollection<TEXTURE_DB_ITEM>();

            using (var file = File.Open(Path.Combine(Environment.CurrentDirectory, Constants.TEXTURE_DB_NAME), FileMode.Open))
            {
                using (var sr = new StreamReader(file))
                {
                    while (!sr.EndOfStream)
                    {
                        var line = sr.ReadLine();

                        var item = new TEXTURE_DB_ITEM
                        {
                            FileName = Path.Combine(Path.Combine(Environment.CurrentDirectory, Constants.TEXTURE_PATH), line.Split(' ')[1]),
                            ID = Convert.ToInt32(line.Split(' ')[0])
                        };

                        Textures.Add(item);
                    }
                }
            }
        }
    }
}