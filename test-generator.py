import sys
import os
from openai import OpenAI

def run_test_generator(target_file):
    client = OpenAI(
        api_key="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",
        base_url="https://api.groq.com/openai/v1"
    )

    if not os.path.exists(target_file):
        print("Файл не найден")
        return

    with open(target_file, 'r') as f:
        source_code = f.read()

    prompt = f"""
    Act as a senior developer. Perform white-box testing for the code below.
    Analyze all logical branches, conditions, and edge cases.
    Generate a complete test suite to achieve maximum code coverage.
    Return only the source code for the tests without any explanation.
    
    Source code:
    {source_code}
    """

    response = client.chat.completions.create(
        model="llama-3.3-70b-versatile",
        messages=[{"role": "user", "content": prompt}]
    )

    output_content = response.choices[0].message.content
    
    if "```" in output_content:
        parts = output_content.split("```")
        for part in parts:
            part = part.strip()
            if any(keyword in part for keyword in ["include", "void", "int", "TEST", "assert"]):
                output_content = part
                break
        
        lines = output_content.split("\n")
        if lines and (lines[0].lower().startswith("cpp") or lines[0].lower().startswith("c++") or lines[0].lower().startswith("python")):
            output_content = "\n".join(lines[1:])

    output_filename = f"generated_test_{os.path.basename(target_file)}"
    with open(output_filename, 'w') as f:
        f.write(output_content.strip())
    print(f"Готово! Актуальная модель Llama 3.3 создала тесты в {output_filename}")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        run_test_generator(sys.argv[1])
    else:
        print("Использование: python3 script.py <filename>")