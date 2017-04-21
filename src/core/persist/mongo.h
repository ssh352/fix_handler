
#ifndef __FH_CORE_PERSIST_MONGO_H__
#define __FH_CORE_PERSIST_MONGO_H__

#include <vector>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include "core/global.h"

namespace fh
{
namespace core
{
namespace persist
{
    class Mongo
    {
        public:
            Mongo(const std::string &db_url, const std::string &db_name, std::uint32_t page_size);
            virtual ~Mongo();

        public:
            // 将指定内容插入到数据库（目标 collection 由 json 中的 market 属性的值确定）
            void Insert(const std::string &json);
            // 从指定 market 对应的 collection 中检索指定日期时间范围内从指定位置开始的数据（检索的最大条数由配置文件决定）
            // start_date_include, end_date_exclude: "yyyy-MM-dd HH:mm:ss" 格式
            // prev_last_record_insert_time: 分页用。0 表示从上述范围内第一条数据开始检索；
            bool Query(std::vector<std::string> &result, const std::string &market,
                                  const std::string &start_date_include, const std::string &end_date_exclude,
                                  std::uint64_t prev_last_record_insert_time = 0);

        private:
            mongocxx::instance m_instance;
            mongocxx::client m_client;
            mongocxx::database m_db;
            std::uint32_t m_page_size;

        private:
			DISALLOW_COPY_AND_ASSIGN(Mongo);
    };
} // namespace persist
} // namespace core
} // namespace fh

#endif // __FH_CORE_PERSIST_MONGO_H__
