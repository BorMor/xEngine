#include "xEngine.h"

class xShaderPreprocessor
{
public:
	static xString LoadContents(const xString& path)
	{
		xString dir, name;
		Explode(path, dir, name);
		return xShaderPreprocessor().Prepare(dir, name);
	}
protected:
	xList<xString>	mProcessedFiles;

	static void Explode(const xString& path, xString& dir, xString& name)
	{
		int npos = 0;
		for (int i = path.Length() - 1; i >= 0; --i)
			if (path[i] == '/' || path[i] == '\\')
			{
				npos = i + 1;
				break;
			}
		dir = xString(path.c_str(), npos);
		name = xString(path.c_str() + npos);
	}

	xString Prepare(const xString& dir, const xString& name)
	{
		xString path = dir + name;

		//@todo: convert to absolute path

		if (mProcessedFiles.Find(path) != mProcessedFiles.End())
			return "";

		mProcessedFiles.AddBack(path);		
		
		// Read contents
		xString source = xFile::ReadToString(path);
		// Remove single-line comments
		source = xRegex::Replace(source, "//.*\\n?", "", xRegexOptions::Multiline);
		// Remove multi-line comments
		source = xRegex::Replace(source, "/\\*(.|[\\r\\n])*?\\*/", "", xRegexOptions::Multiline);
		
		// Replace #include "..." statements
		xString text;
		xMatchCollection matches;
		if (xRegex::Matches(source, "(?:#include\\s*\"(.*?)\")", matches, xRegexOptions::Multiline))
		{
			size_t index = 0;
			for (xMatchCollection::Iterator it = matches.Begin(); it != matches.End(); ++it)
			{
				// Concatenate part before match
				text += source.SubString(index, (*it)->Index() - index);

				// Replace with content
				xString include = (*it)->Groups[0].Value();
				xString left, right;
				Explode(include, left, right);
				text += Prepare(dir + left, right);

				index = (*it)->Index() + (*it)->Length();
			}
			// Concatenate remainded chars
			size_t remains = source.Length() - index;
			if (remains)
				text += source.SubString(index, remains);
		}
		else
			text = source;
		
		return text;
	}
};