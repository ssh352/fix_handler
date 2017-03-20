
#include <stdio.h>
#ifdef __unix__
#include <execinfo.h>
#endif
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "core/global.h"
#include "core/assist/logger.h"

#include "cme/exchange/exchange_application.h"

void handler(int sig)
{
#ifdef __unix__
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
#endif
}

int main(int argc, char* argv[])
{
    signal(SIGSEGV, handler);

    try
    {
        if (argc != 2 || (strcmp(argv[1], "-s") != 0 && strcmp(argv[1], "-j") != 0))
        {
            LOG_ERROR("Usage: exchange_client_test -s|-j");
            return 1;
        }

        fh::core::assist::Logger::Set_level(fh::core::assist::Logger::Level::INFO);
        bool is_week_begin = (strcmp(argv[1], "-s") == 0);
        fh::cme::exchange::ExchangeApplication a(nullptr, is_week_begin);
        a.Start(std::vector<::pb::ems::Order>());

        std::cin.get();
        a.Stop();
    }
    catch (std::exception& e)
    {
        LOG_ERROR("Exception: ", e.what());
    }

    return 0;
}

// ./exchange_client_test -s
