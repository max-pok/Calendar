#pragma once
namespace Globals
{
	using namespace System;
	public ref class GlobalClass
	{
	public: 
		static String^ day;
		static String^ month;
		static String^ year;
		static String^ user_id;
		static String^ password;
		static String^ event_name;
		static String^ priority;
		static String^ hour;
		static String^ minute;
		static String^ eventType;
		static String^ team_name;
		static String^ old_event_name;
		static String^ old_priority;
		static String^ old_eventType;
		static String^ old_hour;
		static String^ old_minute;
		static bool resetActivation = false;
	};
}