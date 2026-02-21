using System.Text;

static string ConvertPngToUnsignedCharArray(string filePath)
{
	byte[] bytes = File.ReadAllBytes(filePath);

	Console.WriteLine($"Read {bytes.Length} bytes from {filePath}");
	StringBuilder sb = new StringBuilder();
	sb.AppendLine("{");

	for (int i = 0; i < bytes.Length; i++)
	{
		sb.Append("  0x");
		sb.Append(bytes[i].ToString("X2"));

		if (i < bytes.Length - 1)
			sb.Append(",");

		if ((i + 1) % 12 == 0) // 12 bytes per line for readability
			sb.AppendLine();
		else
			sb.Append(" ");
	}

	sb.AppendLine();
	sb.Append("}");

	return sb.ToString();
}

string filePath = @"../../../../../../../docs/skyemu-theme-default.png";
string output = ConvertPngToUnsignedCharArray(filePath);

File.WriteAllText("output.txt", output);
