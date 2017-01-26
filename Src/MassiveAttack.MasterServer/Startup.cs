using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

using MassiveAttack.MasterServer.Abstractions;
using MassiveAttack.MasterServer.Implementations.Redis;
using MassiveAttack.MasterServer.Objects;

namespace MassiveAttack.MasterServer
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

        public void ConfigureServices(IServiceCollection services)
        {
            services.Configure<GlobalSettings>(Configuration.GetSection("GlobalSettings"));

            services.AddMvc();

            var globalSettings = new GlobalSettings();
            Configuration.GetSection("Settings").Bind(globalSettings);

            // TODO: As additional implementations are implemented such as SQL Server, MongoDB etc read from the settings file
            services.AddTransient<IGameServerList>(a => new RedisGameServerList(globalSettings.DBConnectionString));
        }

        public void Configure(IApplicationBuilder app, IHostingEnvironment env, ILoggerFactory loggerFactory)
        {
            loggerFactory.AddConsole(Configuration.GetSection("Logging"));
            loggerFactory.AddDebug();

            app.UseMvc();
        }
    }
}