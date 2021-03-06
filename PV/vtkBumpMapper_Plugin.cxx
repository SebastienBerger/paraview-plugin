/*=========================================================================

   Program: ParaView
   Module:    pqParaViewPlugin.cxx.in

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2. 

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/
#include "vtkBumpMapper_Plugin.h"

#include "vtkObjectFactory.h"

#include "/import/etud/43/sberger/Bureau/visualisation/paraview/BumpMapper/PV/vtkSMXML_vtkBumpMapper.h"

#include "/import/etud/43/sberger/Bureau/visualisation/paraview/BumpMapper/PV/vtkBumpMapper_doc.h"

//-----------------------------------------------------------------------------
// Used to push a string returns from a function to a vector.
template <class T, class F>
void PushBack(T& vector, F& fun)
{
  char* text = fun();
  vector.push_back(text);
  delete []text;
}

//-----------------------------------------------------------------------------
#ifdef plugin_type_servermanager
# if defined(INITIALIZE_WRAPPING) || defined(INITIALIZE_EXTRA_CS_MODULES)
#  include "vtkClientServerInterpreterInitializer.h"
#  include "vtkClientServerInterpreter.h"

#   if defined(INITIALIZE_WRAPPING)
extern "C" void vtkBumpMapper_Initialize(vtkClientServerInterpreter *);
#   endif



extern "C" void VTK_EXPORT vtkBumpMapper_CombinedInitialize(
  vtkClientServerInterpreter *interp)
{
#   if defined(INITIALIZE_WRAPPING)
  vtkBumpMapper_Initialize(interp);
#   endif

  // Now initialize any extra kits as requested.
  
}
# endif
#endif

//-----------------------------------------------------------------------------
void vtkBumpMapper_Plugin::GetBinaryResources(
  std::vector<std::string>& resources)
{
  PushBack(resources, vtkBumpMapper_doc);

  (void)resources;
}

//-----------------------------------------------------------------------------
#ifdef plugin_type_gui


#endif

//-----------------------------------------------------------------------------
#ifdef plugin_type_servermanager
vtkClientServerInterpreterInitializer::InterpreterInitializationCallback
vtkBumpMapper_Plugin::GetInitializeInterpreterCallback()
{
# if defined(INITIALIZE_WRAPPING) || defined(INITIALIZE_EXTRA_CS_MODULES)
  return vtkBumpMapper_CombinedInitialize;
# endif
  return NULL;
}

//-----------------------------------------------------------------------------
void vtkBumpMapper_Plugin::GetXMLs(std::vector<std::string> &xmls)
{
  PushBack(xmls, vtkBumpMappervtkBumpMapperInterfaces);

  (void)xmls;
}
#endif

//-----------------------------------------------------------------------------
#ifdef plugin_type_gui
QObjectList vtkBumpMapper_Plugin::interfaces()
{
  QObjectList ifaces;
#ifdef PUSH_BACK_PV_INTERFACES
  PUSH_BACK_PV_INTERFACES(ifaces);
#endif
  return ifaces;
}
#endif

//-----------------------------------------------------------------------------
#ifdef plugin_type_python


void vtkBumpMapper_Plugin::GetPythonSourceList(std::vector<std::string>& modules,
  std::vector<std::string>& sources,
  std::vector<int> &package_flags)
{
  const char *moduleNames[] = {
    
  };
  char *moduleSources[] = {
    
  };
  const int packageFlags[] = {
    
  };

  int num_modules = sizeof(moduleNames)/sizeof(const char *);
  for (int cc=0; cc < num_modules; cc++)
    {
    modules.push_back(moduleNames[cc]);
    sources.push_back(moduleSources[cc]);
    package_flags.push_back(packageFlags[cc]);

    // free allocated memory.
    delete moduleSources[cc];
    moduleSources[cc] = NULL;
    }
}
#endif

//-----------------------------------------------------------------------------
vtkBumpMapper_Plugin::vtkBumpMapper_Plugin()
{
#ifndef BUILD_SHARED_LIBS
# ifdef plugin_type_gui
  // For static builds, initialize the Qt resources as well as the Qt plugin.
  
  Q_IMPORT_PLUGIN(vtkBumpMapper)
# endif
#endif
}

//-----------------------------------------------------------------------------
// Mark this as a ParaView-ServerManager plugin.
PV_PLUGIN_EXPORT(vtkBumpMapper, vtkBumpMapper_Plugin)

//-----------------------------------------------------------------------------
#ifdef plugin_type_gui
// Required to mark this as a Qt plugin.
#if QT_VERSION >= 0x050000
Q_DECLARE_INTERFACE(vtkBumpMapper_Plugin, "com.kitware/paraview/vtkBumpMapper")
Q_PLUGIN_METADATA(IID "com.kitware/paraview/vtkBumpMapper")
#else
Q_EXPORT_PLUGIN2(vtkBumpMapper,  vtkBumpMapper_Plugin)
#endif
#endif
