using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace SocketDrawer
{
    /// <summary>
    /// App.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class App : Application
    {
        void app_Startup(object sender, StartupEventArgs e)
        {
            if (e.Args.Length == 1)
            {
                Arguments.Port = int.Parse(e.Args[0]);
            }
            else if (e.Args.Length ==2)
            {
                Arguments.Ip = e.Args[0];
                Arguments.Port = int.Parse(e.Args[1]);
            }
        }
    }
}
