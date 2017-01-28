using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

using MassiveAttack.MasterServer.WebAPI.Abstractions;
using MassiveAttack.MasterServer.WebAPI.Implementations.Redis;
using MassiveAttack.MasterServer.WebAPI.Objects;

namespace MassiveAttack.MasterServer.WebAPI
{
    public class Startup
    {
        public Startup(IHostingEnvironment env)
        {
            var builder = new ConfigurationBuilder()
               .SetBasePath(env.ContentRootPath)
               .AddJsonFile("appsettings.json", optional: true, reloadOnChange: true)
               .AddEnvironmentVariables();
            Configuration = builder.Build();
        }

        public IConfigurationRoot Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.Configure<GlobalSettings>(Configuration.GetSection("GlobalSettings"));

            services.AddMvc();

            var globalSettings = new GlobalSettings();
            Configuration.GetSection("Settings").Bind(globalSettings);

            // TODO: As additional implementations are implemented such as SQL Server, MongoDB etc read from the settings file
            services.AddTransient<IGameServerList>(a => new RedisGameServerList(globalSettings.DBConnectionString));
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IHostingEnvironment env, ILoggerFactory loggerFactory)
        {
            app.UseMvc();
        }
    }
}
