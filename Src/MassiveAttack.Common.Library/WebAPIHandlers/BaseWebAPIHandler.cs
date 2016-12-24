using System.Net.Http;
using System.Threading.Tasks;
using MassiveAttack.Common.Library.Objects.Common;
using Newtonsoft.Json;

namespace MassiveAttack.Common.Library.WebAPIHandlers {
    public class BaseWebAPIHandler {
        private HttpClient _httpClient;

        private readonly string _token;
        private readonly string _webapiAddress;

        public BaseWebAPIHandler(HandlerConstructorItem constructorItem) {
            _webapiAddress = constructorItem.WebAPIService;
            _token = constructorItem.Token;
            IsOnline = true;
        }

        public bool IsOnline { get; private set; }

        private HttpClient GetHttpClient() {
            _httpClient = new HttpClient();

            if (!string.IsNullOrEmpty(_token)) {
                _httpClient.DefaultRequestHeaders.Add("Token", _token);
            }

            return _httpClient;
        }

        private string BuildUrl(string relativeURL) => $"{_webapiAddress}{relativeURL}";

        public async Task<T> GetAsync<T>(string relativeURL) {
            var result = await GetHttpClient().GetStringAsync(BuildUrl(relativeURL));

            return (T)JsonConvert.DeserializeObject(result);
        }

        public async Task<TK> PutAsync<T, TK>(string relativeURL, T objectValue) {
            var result = await GetHttpClient().PutAsync(BuildUrl(relativeURL), new MultipartContent());

            return (TK)JsonConvert.DeserializeObject(await result.Content.ReadAsStringAsync());
        }
    }
}