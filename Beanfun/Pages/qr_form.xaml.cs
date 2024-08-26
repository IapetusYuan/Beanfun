using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Beanfun
{
    /// <summary>
    /// qr_form.xaml 的交互逻辑
    /// </summary>
    public partial class qr_form : Page
    {
        public qr_form()
        {
            InitializeComponent();
        }

        private void btn_Refresh_QRCode_Click(object sender, RoutedEventArgs e)
        {
            App.MainWnd.refreshQRCode();
        }

        private void btn_Refresh_QRCode_MouseEnter(object sender, MouseEventArgs e)
        {
            if (qr_Tip.Visibility == Visibility.Collapsed)
            {
                DockPanel.SetDock(btn_Refresh_QRCode, Dock.Left);
                qr_Tip.Visibility = Visibility.Visible;
            }
        }

        private void qr_Tip_Click(object sender, RoutedEventArgs e)
        {
            Process.Start("https://tw.beanfun.com/bfevent/bfApp/Page20160930/PC/index.html");
        }

        private void btn_get_qr_url_Click(object sender, RoutedEventArgs e)
        {
            string url = App.MainWnd.decodeQRCode();
            UrlTextBox.Text = url;

        }

        private void TextBlock_MouseLeave(object sender, MouseEventArgs e)
        {
            if (qr_Tip.Visibility == Visibility.Visible)
            {
                DockPanel.SetDock(btn_Refresh_QRCode, Dock.Top);
                qr_Tip.Visibility = Visibility.Collapsed;
            }
        }

        private void btn_back_Click(object sender, RoutedEventArgs e)
        {
            App.LoginMethod = (int)LoginMethod.Regular;
            App.MainWnd.loginMethodChanged();
        }

        private void UrlTextBox_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (UrlTextBox.Text == "" ) return;
            try
            {
                Clipboard.SetText(UrlTextBox.Text);
            }
            catch { }
        }

        private void btn_get_qr_url(object sender, RoutedEventArgs e)
        {
            App.LoginMethod = (int)LoginMethod.Regular;
            App.MainWnd.loginMethodChanged();
        }
    }
}
