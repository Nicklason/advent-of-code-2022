FROM mcr.microsoft.com/dotnet/sdk:6.0 AS build
WORKDIR /app
RUN dotnet new console
COPY Program.cs Program.cs
RUN dotnet publish -c Release -o out

FROM mcr.microsoft.com/dotnet/runtime:6.0
WORKDIR /app
COPY --from=build /app/out .
COPY input.txt .
ENTRYPOINT ["dotnet", "app.dll"]
