#include "Multithread.hpp"

namespace CUtils
{
   Multithread::~Multithread()
   {
      JoinAll();	   
   }

   void Multithread::Run()
   {
      for (auto& task : tasks)
      {
	 threads.push_back(std::thread([task]()
	 {
            try
	    {
               task();
	    }

	    catch (const std::exception& e)
	    {
	       std::cerr << "Error in the thread: " << e.what() << std::endl;
	    }

	 }));
      }
   }

   void Multithread::JoinAll()
   {
      for (auto& t : threads)
      {
	 if (t.joinable())
	 {
             t.join();		 
	 }
      }	      
   }

   void Multithread::JoinOne(std::thread& t)
   {
      if (t.joinable())
      {
	  t.join();
      }
   }

   void Multithread::CancelAll()
   {
      for (auto& t : threads)
      {
	  if (t.joinable())
	  {
              t.detach();
	  }
      }

      threads.clear();
   }
}
