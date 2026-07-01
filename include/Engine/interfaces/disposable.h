#pragma once

class Disposable
{
public:
   virtual ~Disposable();

   void dispose() {
      if (disposed) return;
      disposed = true;
      on_dispose();
   }

   bool is_valid() const {
      return !disposed;
   }

   bool is_invalid() const {
      return disposed;
   }

protected:
   virtual void on_dispose() = 0;

private:
   bool disposed = false;
};
