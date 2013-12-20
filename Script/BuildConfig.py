import sys
import optparse

import LibWorkspace
import LibBuildCode

def StartFromCommandLine( argv ) :	
    usage = "usage: %prog [options] buildConfigName"
    parser = optparse.OptionParser(usage=usage)
    parser.add_option(u"-c", u"--clean", help="Clean Project", action="store_true",  dest="Clean")
    parser.add_option(u"-r", u"--rebuild", help="Rebuild Project", action="store_true",  dest="Rebuild")
    (options, args) = parser.parse_args()
    
    if len( args ) != 1 :
        print("Error: invalid argument count")
        exit()
          
    workspace = LibWorkspace.GetWorkspace( "Sable" )
    if workspace == None :
        print( "Error: Invalid workspace name" )
        exit()
        
    project = workspace.GetProject( "Sable" )
    if project == None :
        print( "Error: Invalid project name" )
        exit()
        
    buildConfig = project.GetBuildConfig( args[0] )
    if buildConfig == None :
        print( "Error: Invalid build config name" )
        exit()
     
    builder = LibBuildCode.CreateBuilder( buildConfig )
    if builder == None :
        print( "Error: Failled to create builder")
        exit()
        
    if options.Clean == True :
        builder.Clean()
    elif options.Rebuild == True :
        builder.ReBuild()
    else :
        builder.Build()    
    
"""
Build a project config for a given platform

option: 
    -c Clean build file for that config
    -r Rebuild file for that config
    
arguments:
    

"""     
def Main( argv ) :	

    try:
        StartFromCommandLine( argv )
    except (KeyboardInterrupt):
        exit()
    
Main( sys.argv )
