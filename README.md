hook-journal

hook-journal é uma DLL para Windows que intercepta chamadas à API DeviceIoControl e filtra entradas do USN Journal (NTFS) com base numa lista configurável de nomes de arquivos bloqueados. É útil para cenários de segurança, monitoramento ou anti-adulteração, quando é necessário ocultar ou bloquear determinadas atividades de arquivo detectadas por ferramentas que leem o USN Journal.

✨ Principais características

🪝 Ganchos em DeviceIoControl implementados com MinHook.

🛡️ Filtragem de registros USN_RECORD retornados por FSCTL_READ_USN_JOURNAL — registros cujo nome de arquivo corresponder à lista de bloqueio são removidos/omitidos.

⚙️ Lista de nomes de arquivos bloqueados facilmente configurável no código-fonte.

🔧 Compatível com injeção de DLL em processos que consultam o USN Journal.

🚀 Como usar

🛠️ Compile a DLL no Visual Studio (recomenda-se 2019 ou posterior).

💉 Injete a DLL compilada no processo de destino (por exemplo, usando um injetor de DLL).

🔍 Ao interceptar chamadas a DeviceIoControl para FSCTL_READ_USN_JOURNAL, o gancho filtra automaticamente os USN_RECORD que contenham nomes bloqueados.

🏗️ Requisitos e build

💻 Visual Studio (2019 ou mais recente recomendado).

📦 MinHook incluída no repositório (ou link para submódulo).

Instruções de build: abra a solução no Visual Studio, selecione a configuração desejada (Release/Debug) e compile.

Depois de gerar a DLL, use seu mecanismo preferido para injetá-la no processo alvo.

⚠️ Avisos e considerações

Este projeto altera o comportamento de chamadas de baixo nível do sistema — use apenas em ambientes de teste/avaliação ou conforme a legislação e políticas aplicáveis.

Injeção de DLL em processos de terceiros pode ser detectada por soluções antimalware ou violar termos de uso.
