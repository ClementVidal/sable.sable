import LibWorkspace
import LibGenerateCode

w = LibWorkspace.GetWorkspace( "Sable" )
LibGenerateCode.GenerateHeader( w )
LibGenerateCode.GenerateBuildFile( w )
