'''
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre™. All rights reserved.
    
    Apport hook for narayan-designer.
    
    Note: This isn't usable yet since at this time Apport submits bug reports
    only to Launchpad. We do not host our issue tracker there, but on GitHub.
'''

import os.path
from apport.hookutils import *

opencl_packages = 
[
    'beignet-opencl-icd',
    'clinfo',
    'mesa-opencl-icd',
    'nvidia-libopencl1-304',
    'nvidia-libopencl1-304',
    'nvidia-libopencl1-340',
    'nvidia-libopencl1-384',
    'oclgrind',
    'ocl-icd-libopencl1',
    'pocl-opencl-icd'
  ]

def add_info(report):

    # This isn't an official Ubuntu package, so provide name...
    if not apport.packaging.is_distro_package(report['Package'].split()[0]):
        report['CrashDB'] = 'narayan-designer'

    # Attach hardware report...
    attach_hardware(report)
    
    # Show OpenCL package versions...
    versions = ''
    for package in opencl_packages:
        try:
            version = packaging.get_version(package)
        except ValueError:
            version = 'N/A'
        versions += '%s %s\n' % (package, version)
    report['DriverPackageVersions'] = versions

    # Attach the output of clinfo(1) if available...
    if command_available('clinfo'):
        report['OpenCL Info'] = command_output('clinfo')
    else:
        report['OpenCL Info'] = 'clinfo not found in path...'

    # Attach the GPU manager log...
    attach_file_if_exists(report, '/var/log/gpu-manager.log', 'GpuManagerLog')

    # Report suspicious X errors...
    report['SuspiciousXErrors'] = xsession_errors(re.compile('CRITICAL.*assertion.*failed'))

