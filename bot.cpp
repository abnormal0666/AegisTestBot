#include <aegis.hpp>
#include <fstream>
#include "main.h"
#include "config.h"

int main()
{
	aegis::core bot(aegis::create_bot_t().log_level(spdlog::level::trace).token(BOT_TOKEN));


	bot.set_on_message_create([](aegis::gateway::events::message_create obj)
		{
			const aegis::snowflake channel_id = obj.msg.get_channel().get_id();
			const aegis::snowflake guild_id = obj.msg.get_guild().get_id();
			const aegis::snowflake message_id = obj.msg.get_id();
			const aegis::snowflake is_bot = obj.get_user().is_bot();
			const aegis::snowflake user_id = obj.msg.get_author_id();

			std::string content{ obj.msg.get_content() };
			std::string usermention = std::string("<@!") + user_id.gets() + std::string(">");
			std::string channelmention = std::string("<#") + user_id.gets() + std::string(">");
			std::string rolemention = std::string("<@&") + user_id.gets() + std::string(">");

			using embed = aegis::gateway::objects::embed;
			using field = aegis::gateway::objects::field;
			using aegis::gateway::objects::image;

			auto& _channel = obj.msg.get_channel();
			auto& _guild = _channel.get_guild();
			auto& username = obj.msg.author.username;



			if (is_bot) return;
			if (content == CPP" prefix" or content == "prefix")
			{
				_channel.create_message
				(
					COBRA"'s prefix is either ``!co`` or ``>`` \n" 
					COBRATURRET"'s prefix is ``<`` or some ``/`` commands \n" 
					CPP" is a special case, as you can only @mention or trigger key words (see <@!844003621591056414> triggers)"
				);
			}
			if (content == CPP" website" or content == "website") 
			{
				_channel.create_message(WEBSITE);

			}
			if (content == CPP" playlist" or content == "playlist")
			{
				_channel.create_message("Wanna listen to what my dev listens to? Now you can with \n" PLAYLIST);
			}
			if (content == CPP" help" or content == "help")
			{
				_channel.create_message("https://github.com/abnormal0666/AegisTestBot/blob/master/README.md#commands");
			}
			if (content == CPP" triggers" or content == "triggers")
			{
				_channel.create_message("``playlist``, ``help``, ``website``, ``prefix``");
			}
			if (content == CPP" embed") 
			{
				_channel.create_message(aegis::create_message_t()
					.embed(
						embed()
						.color(0xFF0000)
						.title("Title")
						.description("Description")
						.image(image{ "https://webforpc.com/wp-content/uploads/2018/03/c-plus-plus-program-logo-image.png" })
						.fields
						({
							field()
							.name("Field Name")
							.value("Value")
							.is_inline(true),

							field()
							.name("Field 2")
							.value("Value")
							.is_inline(true)
							})
					)
				);
			}
		});

	bot.run();
	bot.yield();
}
